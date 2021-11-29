//=================== dts 
			gpio-keys {
				compatible = "simple,gpio-keys";

				recovery-key {
					key_gpios = <PAD_KEY0>;
					key,active_low;
					linux,code = <0x200>;
					label = "recovery";
					debounce-interval = <1>;
					wakeup-source;
				};
			};
         };
 
 };


//===================================驱动 kernel\drivers\misc

/*
 * Driver for keys on GPIO lines capable of generating interrupts.
 *
 * Copyright 2005 Phil Blundell
 * Copyright 2010, 2011 David Jander <david@protonic.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/pm.h>
#include <linux/slab.h>
#include <linux/sysctl.h>
#include <linux/proc_fs.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/gpio_keys.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>
#include <linux/gpio/consumer.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/spinlock.h>
#include <linux/miscdevice.h>
#include<linux/uaccess.h>

#ifdef CONFIG_ARCH_SSTAR
int key_status;
#endif

struct gpio_button_data {
	const struct gpio_keys_button *button;
	struct gpio_desc *gpiod;

	struct timer_list release_timer;
	unsigned int release_delay;	/* in msecs, for IRQ-only buttons */

	struct delayed_work work;
	unsigned int software_debounce;	/* in msecs, for GPIO-driven buttons */

	unsigned int irq;
	spinlock_t lock;
	bool disabled;
	bool key_pressed;
};

struct gpio_keys_drvdata {
	const struct gpio_keys_platform_data *pdata;
	//struct mutex disable_lock;
	struct gpio_button_data data[0];
};
wait_queue_head_t key_queue;
static int g_key_value = 0;
static int g_condition = 0;

static void gpio_keys_gpio_report_event(struct gpio_button_data *bdata)
{
	int state;

	state = gpiod_get_value_cansleep(bdata->gpiod);
	if (state < 0) {
		printk("gpio_keys: failed to get gpio state: %d\n", state);
		return;
	}
#ifdef CONFIG_ARCH_SSTAR
	if(key_status==state)
	{
		pr_debug("false trigger");
		return;
	}
	key_status = state;

	if(key_status)
	{
		irq_set_irq_type(bdata->irq,IRQF_TRIGGER_RISING);
	}
	else
	{
		irq_set_irq_type(bdata->irq,IRQF_TRIGGER_FALLING);
			
	}

	//printk("gpio_keys_gpio_report_event: state=%d\r\n", state);
#endif

	g_condition = 1;
	g_key_value = state;
	wake_up_interruptible(&key_queue);
}

static void gpio_keys_gpio_work_func(struct work_struct *work)
{
	struct gpio_button_data *bdata =
		container_of(work, struct gpio_button_data, work.work);

	gpio_keys_gpio_report_event(bdata);
}

static irqreturn_t gpio_keys_gpio_isr(int irq, void *dev_id)
{
	struct gpio_button_data *bdata = dev_id;

	BUG_ON(irq != bdata->irq);

	mod_delayed_work(system_wq,
			 &bdata->work,
			 msecs_to_jiffies(bdata->software_debounce));

	return IRQ_HANDLED;
}

static void gpio_keys_quiesce_key(void *data)
{
	struct gpio_button_data *bdata = data;

	if (bdata->gpiod)
		cancel_delayed_work_sync(&bdata->work);
	else
		del_timer_sync(&bdata->release_timer);
}

static int gpio_keys_setup_key(struct platform_device *pdev,
				struct gpio_button_data *bdata,
				const struct gpio_keys_button *button)
{
	const char *desc = button->desc ? button->desc : "gpio_keys";
	struct device *dev = &pdev->dev;
	irq_handler_t isr;
	unsigned long irqflags;
	int irq;
	int error;

	bdata->button = button;
	spin_lock_init(&bdata->lock);

	/*
	 * Legacy GPIO number, so request the GPIO here and
	 * convert it to descriptor.
	 */
	if (gpio_is_valid(button->gpio)) {
		unsigned flags = GPIOF_IN;

		if (button->active_low)
			flags |= GPIOF_ACTIVE_LOW;

		error = devm_gpio_request_one(&pdev->dev, button->gpio, flags,
					      desc);
		if (error < 0) {
			dev_err(dev, "Failed to request GPIO %d, error %d\n",
				button->gpio, error);
			return error;
		}

		bdata->gpiod = gpio_to_desc(button->gpio);
		if (!bdata->gpiod)
			return -EINVAL;

		if (button->debounce_interval) {
			error = gpiod_set_debounce(bdata->gpiod,
					button->debounce_interval * 1000);
			/* use timer if gpiolib doesn't provide debounce */
			if (error < 0)
				bdata->software_debounce =
						button->debounce_interval;
		}

		if (button->irq) {
			bdata->irq = button->irq;
		} else {
			irq = gpiod_to_irq(bdata->gpiod);
			if (irq < 0) {
				error = irq;
				dev_err(dev,
					"Unable to get irq number for GPIO %d, error %d\n",
					button->gpio, error);
				return error;
			}
			bdata->irq = irq;
		}

		INIT_DELAYED_WORK(&bdata->work, gpio_keys_gpio_work_func);

		isr = gpio_keys_gpio_isr;
#ifdef CONFIG_ARCH_SSTAR
		key_status = gpiod_get_value_cansleep(bdata->gpiod);
		if (key_status < 0) {
			dev_err(dev,
				"failed to get gpio state: %d\n", key_status);
			return key_status;
		}

		if(key_status)
			irqflags = IRQF_TRIGGER_RISING;
		else
			irqflags = IRQF_TRIGGER_FALLING;

#else
		irqflags = IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING;
#endif
	} else {
		dev_err(dev, "invalid gpio err\n");
		return -EINVAL;
	}

	/*
	 * Install custom action to cancel release timer and
	 * workqueue item.
	 */
	error = devm_add_action(&pdev->dev, gpio_keys_quiesce_key, bdata);
	if (error) {
		dev_err(&pdev->dev,
			"failed to register quiesce action, error: %d\n",
			error);
		return error;
	}

	/*
	 * If platform has specified that the button can be disabled,
	 * we don't want it to share the interrupt line.
	 */
	if (!button->can_disable)
		irqflags |= IRQF_SHARED;

	error = devm_request_any_context_irq(&pdev->dev, bdata->irq,
					     isr, irqflags, desc, bdata);
	if (error < 0) {
		dev_err(dev, "Unable to claim irq %d; error %d\n",
			bdata->irq, error);
		return error;
	}

	return 0;
}

/*
 * Handlers for alternative sources of platform_data
 */

#ifdef CONFIG_OF
/*
 * Translate OpenFirmware node properties into platform_data
 */
static struct gpio_keys_platform_data *
gpio_keys_get_devtree_pdata(struct device *dev)
{
	struct device_node *node, *pp;
	struct gpio_keys_platform_data *pdata;
	struct gpio_keys_button *button;
	//int error;
	int nbuttons;
	int i;

	node = dev->of_node;
	if (!node)
		return ERR_PTR(-ENODEV);

	nbuttons = of_get_available_child_count(node);
	if (nbuttons == 0)
		return ERR_PTR(-ENODEV);

	pdata = devm_kzalloc(dev,
			     sizeof(*pdata) + nbuttons * sizeof(*button),
			     GFP_KERNEL);
	if (!pdata)
		return ERR_PTR(-ENOMEM);

	pdata->buttons = (struct gpio_keys_button *)(pdata + 1);
	pdata->nbuttons = nbuttons;

	pdata->rep = !!of_get_property(node, "autorepeat", NULL);

	of_property_read_string(node, "label", &pdata->name);

	i = 0;
	for_each_available_child_of_node(node, pp) {
		//enum of_gpio_flags flags;

		button = &pdata->buttons[i++];

#if 0
		button->gpio = of_get_gpio_flags(pp, 0, &flags);
		if (button->gpio < 0) {
			error = button->gpio;
			if (error != -ENOENT) {
				if (error != -EPROBE_DEFER)
					dev_err(dev,
						"Failed to get gpio flags, error: %d\n",
						error);
				return ERR_PTR(error);
			}
		} else {
			button->active_low = flags & OF_GPIO_ACTIVE_LOW;
		}
#else
		if(0 != of_property_read_u32(pp, "key_gpios", &button->gpio)){
			return ERR_PTR(-EINVAL);
		}
		
		if (of_property_read_bool(pp, "key,active_low")){
			button->active_low = 1;
		}
#endif

		button->irq = irq_of_parse_and_map(pp, 0);

		if (!gpio_is_valid(button->gpio) && !button->irq) {
			dev_err(dev, "Found button without gpios or irqs\n");
			return ERR_PTR(-EINVAL);
		}

		if (of_property_read_u32(pp, "linux,code", &button->code)) {
			dev_err(dev, "Button without keycode: 0x%x\n",
				button->gpio);
			return ERR_PTR(-EINVAL);
		}

		button->desc = of_get_property(pp, "label", NULL);

		button->wakeup = of_property_read_bool(pp, "wakeup-source") ||
				 /* legacy name */
				 of_property_read_bool(pp, "gpio-key,wakeup");

		button->can_disable = !!of_get_property(pp, "linux,can-disable", NULL);

		if (of_property_read_u32(pp, "debounce-interval",
					 &button->debounce_interval))
			button->debounce_interval = 5;
	}

	if (pdata->nbuttons == 0)
		return ERR_PTR(-EINVAL);

	return pdata;
}

static const struct of_device_id gpio_keys_of_match[] = {
	{ .compatible = "simple,gpio-keys", },
	{ },
};
MODULE_DEVICE_TABLE(of, gpio_keys_of_match);

#else

static inline struct gpio_keys_platform_data *
gpio_keys_get_devtree_pdata(struct device *dev)
{
	return ERR_PTR(-ENODEV);
}

#endif

int key_open(struct inode *node, struct file *filp)
{
	return 0;
}
 
ssize_t key_read(struct file *filp, char __user *buf, size_t size, loff_t *pos)
{
	wait_event_interruptible(key_queue,g_condition);
	if (g_condition == 0) {
		g_key_value = 2;
	}

	//printk(KERN_WARNING"[in kernel]:key num is %d\n",g_key_value);	
	if (copy_to_user(buf, &g_key_value, 4) ){
		g_condition = 0;
		return -EFAULT;	
	}

	g_condition = 0;
	return 4;
}
 
struct file_operations key_fops = 
{
	.open = key_open,
	.read = key_read,
};
 
struct miscdevice key_miscdev =
{
	.minor = 200,
	.name = "gpio_key",
	.fops = &key_fops,
};

static int gpio_keys_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct gpio_keys_platform_data *pdata = dev_get_platdata(dev);
	struct gpio_keys_drvdata *ddata;
	int i, error;
	int wakeup = 0;
	int size;

	if (!pdata) {
		pdata = gpio_keys_get_devtree_pdata(dev);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
	}
	size = sizeof(struct gpio_keys_drvdata) +
			pdata->nbuttons * sizeof(struct gpio_button_data);
	ddata = devm_kzalloc(dev, size, GFP_KERNEL);
	if (!ddata) {
		dev_err(dev, "failed to allocate state\n");
		return -ENOMEM;
	}

	for (i = 0; i < pdata->nbuttons; i++) {
		const struct gpio_keys_button *button = &pdata->buttons[i];
		struct gpio_button_data *bdata = &ddata->data[i];

		error = gpio_keys_setup_key(pdev, bdata, button);
		if (error)
			return error;

		if (button->wakeup)
			wakeup = 1;
	}

	misc_register(&key_miscdev);
	init_waitqueue_head(&key_queue);
	return 0;
}

static int gpio_keys_remove(struct platform_device *pdev)
{
	device_init_wakeup(&pdev->dev, 0);

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int gpio_keys_suspend(struct device *dev)
{
	return 0;
}

static int gpio_keys_resume(struct device *dev)
{
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(gpio_keys_pm_ops, gpio_keys_suspend, gpio_keys_resume);

static struct platform_driver gpio_keys_device_driver = {
	.probe		= gpio_keys_probe,
	.remove		= gpio_keys_remove,
	.driver		= {
		.name	= "gpio-keys",
		.pm	= &gpio_keys_pm_ops,
		.of_match_table = of_match_ptr(gpio_keys_of_match),
	}
};

static int __init gpio_keys_init(void)
{
	return platform_driver_register(&gpio_keys_device_driver);
}

static void __exit gpio_keys_exit(void)
{
	platform_driver_unregister(&gpio_keys_device_driver);
}

late_initcall(gpio_keys_init);
module_exit(gpio_keys_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Phil Blundell <pb@handhelds.org>");
MODULE_DESCRIPTION("Keyboard driver for GPIOs");
MODULE_ALIAS("platform:gpio-keys");

