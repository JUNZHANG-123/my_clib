 kernel/arch/arm/boot/dts/paperangx2c-fpga.dtsi     |  2 ++
 .../boot/dts/paperangx2c-ssc020a-s01a-padmux.dtsi  |  8 ++---
 .../arch/arm/boot/dts/paperangx2c-ssc020a-s01a.dts | 35 ++++++++++++++++++++++
 kernel/arch/arm/boot/dts/paperangx2c.dtsi          |  2 ++
 .../arm/configs/paperangx2c_ssc020a_s01a_defconfig | 13 ++++----
 kernel/drivers/leds/leds-gpio.c                    | 18 +++++++++--
 readme.txt                                         |  3 ++


--- a/kernel/arch/arm/boot/dts/paperangx2c-ssc020a-s01a.dts
+++ b/kernel/arch/arm/boot/dts/paperangx2c-ssc020a-s01a.dts
@@ -95,6 +95,41 @@
                     interrupt-names = "goodix_int";
                 };
             };
+			
+			gpio-leds-green {
+				status = "ok";
+				compatible = "gpio-leds";
+
+				led-green {
+					label = "led_green";
+					led_gpios = <PAD_GPIO0>;
+					led,active_low;
+				};
+			};
+			
+			gpio-leds-red {
+				status = "ok";
+				compatible = "gpio-leds";
+
+				led-red {
+					label = "led_red";
+					led_gpios = <PAD_GPIO1>;
+					led,active_low;
+				};
+			};
+
         };
 
 };


diff --git a/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig b/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig
index 9280d6c43..79f96191c 100755
--- a/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig
+++ b/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig

+CONFIG_NEW_LEDS=y
+CONFIG_LEDS_CLASS=y
+CONFIG_LEDS_GPIO=y

 
diff --git a/kernel/drivers/leds/leds-gpio.c b/kernel/drivers/leds/leds-gpio.c
index d400dcaf4..25abd120d 100644
--- a/kernel/drivers/leds/leds-gpio.c
+++ b/kernel/drivers/leds/leds-gpio.c
@@ -81,8 +81,8 @@ static int create_gpio_led(const struct gpio_led *template,
 {
 	int ret, state;
 
-	led_dat->gpiod = template->gpiod;
-	if (!led_dat->gpiod) {
+	//led_dat->gpiod = template->gpiod;
+	//if (!led_dat->gpiod) {
 		/*
 		 * This is the legacy code path for platform code that
 		 * still uses GPIO numbers. Ultimately we would like to get
@@ -108,7 +108,7 @@ static int create_gpio_led(const struct gpio_led *template,
 		led_dat->gpiod = gpio_to_desc(template->gpio);
 		if (!led_dat->gpiod)
 			return -EINVAL;
-	}
+	//}
 
 	led_dat->cdev.name = template->name;
 	led_dat->cdev.default_trigger = template->default_trigger;
@@ -159,6 +159,7 @@ static struct gpio_leds_priv *gpio_leds_create(struct platform_device *pdev)
 	struct fwnode_handle *child;
 	struct gpio_leds_priv *priv;
 	int count, ret;
+	
 
 	count = device_get_child_node_count(dev);
 	if (!count)
@@ -174,11 +175,22 @@ static struct gpio_leds_priv *gpio_leds_create(struct platform_device *pdev)
 		const char *state = NULL;
 		struct device_node *np = to_of_node(child);
 
+		#if 0
 		led.gpiod = devm_get_gpiod_from_child(dev, NULL, child);
 		if (IS_ERR(led.gpiod)) {
 			fwnode_handle_put(child);
 			return ERR_CAST(led.gpiod);
 		}
+		#else
+		if(0 != of_property_read_u32(np, "led_gpios", &led.gpio)){
+			return ERR_PTR(-EINVAL);
+		}
+		
+		if (of_property_read_bool(np, "led,active_low")){
+			led.active_low = 1;
+			
+		}
+		#endif
 
 		ret = fwnode_property_read_string(child, "label", &led.name);
 		if (ret && IS_ENABLED(CONFIG_OF) && np)


