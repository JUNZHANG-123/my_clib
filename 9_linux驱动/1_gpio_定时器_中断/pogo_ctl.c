#include <linux/io.h>
#include <linux/clk.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/pinctrl/consumer.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/ctype.h>
#include <linux/sunxi-gpio.h>

//timer
#include <linux/kernel.h>
#include <linux/hrtimer.h>
#include <linux/jiffies.h>

#include "../core.h"

struct gpio_config g_gpio_en;
struct gpio_config g_gpio_s;

// 定时器
struct timer_dev{
	int timeperiod;            //定时器周工作服，单位为ms
	struct timer_list timer;   //定义一个定时器
	spinlock_t lock;           //定义自旋锁  
};
struct timer_dev dev;

struct device_node *npx;

//定时器回调函数
void normal_timer_hander(unsigned long arg)
{
	//修改定时器值并重新启动定时器
	
	static int old_status;
	static int new_status = -1;
	int status, set_direct_status;

	int abc = -1;

	// step 1
	status = gpio_request(g_gpio_s.gpio ,NULL);
	if(status != 0){
		printk("#################    error    status= %d    \n",status);
	}
	// step 2
	set_direct_status = gpio_direction_input(g_gpio_s.gpio);
	if (set_direct_status) {
		printk("#################  set gpio direction input failed!\n");
	}
    // step 3
	new_status = __gpio_get_value(g_gpio_s.gpio);	
	// setp 4
	gpio_free(g_gpio_s.gpio); 
	//---end 

	if(old_status != new_status){
		// step 1
		status = gpio_request(g_gpio_en.gpio,NULL);
		if(status != 0){
			printk("#################    error    status= %d    \n",status);
		}
		// step 2
			
		// step 3
		if(1 == new_status){
			set_direct_status = gpio_direction_output(g_gpio_en.gpio,0);
			if (set_direct_status) {
				printk("set gpio direction input failed!\n");
			}			
			__gpio_set_value(g_gpio_en.gpio, 0);
			printk("g_gpio_en.gpio = %d !\n",g_gpio_en.gpio);
			printk("__gpio_set_value 0 !\n");
			
		}else{
			set_direct_status = gpio_direction_output(g_gpio_en.gpio,1);
			if (set_direct_status) {
				printk("set gpio direction input failed!\n");
			}			
			__gpio_set_value(g_gpio_en.gpio, 1);
			printk("g_gpio_en.gpio = %d !\n",g_gpio_en.gpio);
			printk("__gpio_set_value 1 !\n");
		}
		// step 4
		abc = __gpio_get_value(g_gpio_en.gpio);	
		printk("set %d\n", abc);
	}
	old_status = new_status;
	
	mod_timer(&dev.timer,jiffies + msecs_to_jiffies(1000));
}

static int new_status,old_status;
static irqreturn_t sunxi_pinctrl_irq_handler(int irq, void *dev_id)
{
	int status,set_direct_status;
	// step 1
	new_status = __gpio_get_value(g_gpio_s.gpio);	
	
	if(old_status != new_status){
		if(1 == new_status){
			
			set_direct_status = gpio_direction_output(g_gpio_en.gpio,0);
			if (set_direct_status) {
				printk("set gpio direction input failed!\n");
			}			
			__gpio_set_value(g_gpio_en.gpio, 0);
			printk("g_gpio_en.gpio = %d  set=0 !\n",g_gpio_en.gpio);
			
		}else{
			set_direct_status = gpio_direction_output(g_gpio_en.gpio,1);
			if (set_direct_status) {
				printk("set gpio direction input failed!\n");
			}			
			__gpio_set_value(g_gpio_en.gpio, 1);
			printk("g_gpio_en.gpio = %d  set=1 !\n",g_gpio_en.gpio);
		}		
	}
	old_status = new_status;
//	disable_irq_nosync(irq);
	return IRQ_HANDLED;
}

static int pogo_ctrl_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct gpio_config config;
	int  gpio_s, gpio_en;
	
	int ret;
	int status;	
	int virq;
	
	gpio_s = of_get_named_gpio_flags(np, "pogo_io_s", 0, (enum of_gpio_flags *)&config);
	
	if (!gpio_is_valid(gpio_s)) {
		printk("################# failed to get pogo_io_s\n");
		return -ENODEV;
	}	
	memcpy(&g_gpio_s, &config,sizeof(struct gpio_config));
	
//-------------------------------------------------------	

	virq = gpio_to_irq(gpio_s);
	if (virq < 0) {
		printk("map gpio [%d] to virq [%d] failed !\n ", gpio_s, virq);
		return -EINVAL;
	}
	
//	ret = request_irq(virq, sunxi_pinctrl_irq_handler,
//					IRQF_TRIGGER_HIGH | IRQF_TRIGGER_LOW, "PIN_EINT", NULL);
	ret = devm_request_irq(dev,virq, sunxi_pinctrl_irq_handler,IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING , "PL11_EINT", NULL);		
	
//-------------------------------------------------------	
	gpio_en = of_get_named_gpio_flags(np, "pogo_otg_en", 0,
				       (enum of_gpio_flags *)&config);
					   
	if (!gpio_is_valid(gpio_en)) {
		pr_err("################# failed to get pogo_otg_en\n");
		return -ENODEV;
	}				
	
	memcpy(&g_gpio_en,&config,sizeof(struct gpio_config));
	status = gpio_request(g_gpio_en.gpio,NULL);	
	if(status !=0 ){
		printk("#################    error    status= %d    \n",status);
	}
	
// timer 
//	init_timer(&dev.timer);  //初始化定时器
//	dev.timer.function = normal_timer_hander;
//	dev.timer.expires = jiffies + msecs_to_jiffies(2000);
//	dev.timer.data = (unsigned long)&dev;
//	add_timer(&dev.timer);
	return 0;
}


static int pogo_ctrl_remove(struct platform_device *pdev)
{
	gpio_free(g_gpio_en.gpio);
	gpio_free(g_gpio_s.gpio);
	return -1;
}

static const struct of_device_id gopo_dt_ids[] = {
	{ .compatible = "allwinner,sunxi-pogo_c",  },
	{},
};

static struct platform_driver gopo_ctrl_driver = {
	.probe  = pogo_ctrl_probe,
	.remove = pogo_ctrl_remove,
	.driver = {
		.owner = THIS_MODULE,
		.name = "pogo_c",
		.of_match_table = gopo_dt_ids,
	},	
};

static int __init pogo_init(void)
{
	int ret;
	
	printk("#################        pogo_ctrl_probe    ###################################\n");
	
	ret = platform_driver_register(&gopo_ctrl_driver);
	if (IS_ERR_VALUE(ret)) {
		pr_err("%s: failed, errno %d\n", __func__, ret);
		return -EINVAL;
	}

	return 0;
}

static void __exit pogo_exit(void)
{
	printk("Goodbye World \n");	
}

module_init(pogo_init);      
module_exit(pogo_exit);

MODULE_AUTHOR("The Linux Kernel team");
MODULE_DESCRIPTION("GPIO driver for AMD chipsets");
MODULE_LICENSE("GPL");

