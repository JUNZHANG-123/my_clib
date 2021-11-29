 kernel/arch/arm/boot/dts/paperangx2c-fpga.dtsi     |  2 ++
 .../boot/dts/paperangx2c-ssc020a-s01a-padmux.dtsi  |  8 ++---
 .../arch/arm/boot/dts/paperangx2c-ssc020a-s01a.dts | 35 ++++++++++++++++++++++
 kernel/arch/arm/boot/dts/paperangx2c.dtsi          |  2 ++
 .../arm/configs/paperangx2c_ssc020a_s01a_defconfig | 13 ++++----
 kernel/drivers/input/keyboard/gpio_keys.c          | 14 +++++++--


--- a/kernel/arch/arm/boot/dts/paperangx2c-ssc020a-s01a.dts
+++ b/kernel/arch/arm/boot/dts/paperangx2c-ssc020a-s01a.dts
@@ -95,6 +95,41 @@
                     interrupt-names = "goodix_int";
                 };
             };
+			
+
+			gpio-keys {
+				compatible = "gpio-keys";
+
+				recovery-key {
+					key_gpios = <PAD_KEY0>;
+					key,active_low;
+					linux,code = <0x200>;
+					label = "recovery";
+					debounce-interval = <1>;
+					wakeup-source;
+				};
+			};
         };
 
 };


diff --git a/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig b/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig
index 9280d6c43..79f96191c 100755
--- a/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig
+++ b/kernel/arch/arm/configs/paperangx2c_ssc020a_s01a_defconfig
@@ -1192,7 +1192,8 @@ CONFIG_USB_NET_DRIVERS=y
 #
 # Input device support
 #

+CONFIG_INPUT=y
+CONFIG_INPUT_EVDEV=y
+CONFIG_INPUT_KEYBOARD=y
+CONFIG_KEYBOARD_GPIO=y

diff --git a/kernel/drivers/input/keyboard/gpio_keys.c b/kernel/drivers/input/keyboard/gpio_keys.c
index f3c268b22..6042edc1f 100755
--- a/kernel/drivers/input/keyboard/gpio_keys.c
+++ b/kernel/drivers/input/keyboard/gpio_keys.c
@@ -675,7 +675,7 @@ gpio_keys_get_devtree_pdata(struct device *dev)
 	struct device_node *node, *pp;
 	struct gpio_keys_platform_data *pdata;
 	struct gpio_keys_button *button;
-	int error;
+	//int error;
 	int nbuttons;
 	int i;
 
@@ -702,10 +702,11 @@ gpio_keys_get_devtree_pdata(struct device *dev)
 
 	i = 0;
 	for_each_available_child_of_node(node, pp) {
-		enum of_gpio_flags flags;
+		//enum of_gpio_flags flags;
 
 		button = &pdata->buttons[i++];
 
+#if 0
 		button->gpio = of_get_gpio_flags(pp, 0, &flags);
 		if (button->gpio < 0) {
 			error = button->gpio;
@@ -719,6 +720,15 @@ gpio_keys_get_devtree_pdata(struct device *dev)
 		} else {
 			button->active_low = flags & OF_GPIO_ACTIVE_LOW;
 		}
+#else
+		if(0 != of_property_read_u32(pp, "key_gpios", &button->gpio)){
+			return ERR_PTR(-EINVAL);
+		}
+		
+		if (of_property_read_bool(pp, "key,active_low")){
+			button->active_low = 1;
+		}
+#endif
 
 		button->irq = irq_of_parse_and_map(pp, 0);


