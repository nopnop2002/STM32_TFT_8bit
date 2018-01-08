# STM32_TFT_8bit
STM32 8bit TFT Library

I ported from here.   
https://github.com/prenticedavid/MCUFRIEND_kbv   

----

# Sofware requirement    

Adafruit GFX Library   
https://github.com/adafruit/Adafruit-GFX-Library   

----

# Wirering for 8bit Parallel TFT   

|TFT||STM32F103|
|:-:|:-:|:-:|
|LCD_RST|--|PB7|
|LCD_CS|--|PB6|
|LCD_RS|--|PB5|
|LCD_WR|--|PB4|
|LCD_RD|--|PB3|
|LCD_D0|--|PA0|
|LCD_D1|--|PA1|
|LCD_D2|--|PA2|
|LCD_D3|--|PA3|
|LCD_D4|--|PA4|
|LCD_D5|--|PA5|
|LCD_D6|--|PA6|
|LCD_D7|--|PA7|
|5V|--|5V(*)|
|3.3V|--|3.3V(*)|
|GND|--|GND|

\*When a regulator(It's often AMS1117) is mounted on the back, it's operated 5V.   
\*When a regulator is NOT mounted on the back, it's operated 3.3V.   

Pin define is "STM32_TFT_8bit.h"   

----

# Setting your TFT's resolution    

If your TFT's resolution is NOT 240x320,   
you can set your TFT's resolution using tft.setResoution.   

Exsample:   
```
ID = tft.readID();
tft.setResolution(320, 480); // Set your resolution
Serial.print("Device ID: 0x"); Serial.println(ID, HEX);
tft.begin(ID);
uint32_t width = tft.width();
Serial.print("Width: "); Serial.println(width);
uint32_t height = tft.height();
Serial.print("Height: "); Serial.println(height);
```

---

# R61505 2.4 inch TFT
![r61505](https://user-images.githubusercontent.com/6020549/34552852-70d1e6bc-f167-11e7-8df9-41587ebccc79.JPG)

---

# SPFD5408 2.4 inch TFT
![spfd5408](https://user-images.githubusercontent.com/6020549/34552862-7ae8d62e-f167-11e7-84dd-73b07476cd50.JPG)

---

# ILI9325 2.4 inch TFT
![ili9325](https://user-images.githubusercontent.com/6020549/34552868-848b0fd0-f167-11e7-92f1-9c07e741a33e.JPG)

---

# ILI9341 2.4 inch TFT
![ili9341](https://user-images.githubusercontent.com/6020549/34552875-8eb6c832-f167-11e7-9c8c-7e3e602887d3.JPG)

---

# ILI9342 2.4 inch TFT
![ili9342](https://user-images.githubusercontent.com/6020549/34552887-9aa02fb2-f167-11e7-8ca6-6517de127a4a.JPG)

