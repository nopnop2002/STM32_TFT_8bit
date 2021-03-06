# LCD_ID_Reader
Many controllers are used in the parallel TFT for UNO.   
This is a tool to find the TFT controller.   

# Wirering for 8bit Parallel TFT   

|TFT||STM32F103|
|:-:|:-:|:-:|
|LCD_RST|--|PB7|
|LCD_CS|--|PB6|
|LCD_RS|--|PB5|
|LCD_WR|--|PB4(*2)|
|LCD_RD|--|PB3(*2)|
|LCD_D0|--|PA0|
|LCD_D1|--|PA1|
|LCD_D2|--|PA2|
|LCD_D3|--|PA3|
|LCD_D4|--|PA4|
|LCD_D5|--|PA5|
|LCD_D6|--|PA6|
|LCD_D7|--|PA7|
|5V|--|5V(*1)|
|3.3V|--|3.3V(*1)|
|GND|--|GND|

(*1)When a regulator(It's often AMS1117) is mounted on the back, it's operated 5V.   
When a regulator is NOT mounted on the back, it's operated 3.3V.   

(*2)By several boards, This port is used as JTAG.   
You need remap.   
afio_cfg_debug_ports(AFIO_DEBUG_NONE)   


# Serial print
```
Read Registers on MCUFRIEND UNO shield
controllers either read as single 16-bit
e.g. the ID is at readReg(0)
or as a sequence of 8-bit values
in special locations (first is dummy)

reg(0x0000) 00 00	ID: ILI9320, ILI9325, ILI9335, ...
reg(0x0004) 00 54 80 66	Manufacturer ID
reg(0x0009) 00 00 61 00 00	Status Register
reg(0x000A) 00 08	Get Powsr Mode
reg(0x000C) 00 66	Get Pixel Format
reg(0x0061) 00 00	RDID1 HX8347-G
reg(0x0062) 00 00	RDID2 HX8347-G
reg(0x0063) 00 00	RDID3 HX8347-G
reg(0x0064) 00 00	RDID1 HX8347-A
reg(0x0065) 00 00	RDID2 HX8347-A
reg(0x0066) 00 00	RDID3 HX8347-A
reg(0x0067) 00 00	RDID Himax HX8347-A
reg(0x0070) 00 00	Panel Himax HX8347-A
reg(0x00A1) 00 93 30 93 30	RD_DDB SSD1963
reg(0x00B0) 00 00	RGB Interface Signal Control
reg(0x00B4) 00 00	Inversion Control
reg(0x00B6) 00 02 02 3B 3B	Display Control
reg(0x00B7) 00 06	Entry Mode Set
reg(0x00BF) 00 00 00 00 00 00	ILI9481, HX8357-B
reg(0x00C0) 00 0E 0E 0E 0E 0E 0E 0E 0E	Panel Control
reg(0x00C8) 00 00 00 00 00 00 00 00 00 00 00 00 00	GAMMA
reg(0x00CC) 00 04	Panel Control
reg(0x00D0) 00 00 00	Power Control
reg(0x00D2) 00 00 00 00 00	NVM Read
reg(0x00D3) 00 00 94 86	ILI9341, ILI9488
reg(0x00DA) 00 54	RDID1
reg(0x00DB) 00 80	RDID2
reg(0x00DC) 00 66	RDID3
reg(0x00E0) 00 0F 21 1C 0B 0E 08 49 98 38 09 11 03 14 10 00	GAMMA-P
reg(0x00E1) 00 0F 2F 2B 0C 0E 06 47 76 37 07 11 04 23 1E 00	GAMMA-N
reg(0x00EF) 00 80 00 10 60 40	ILI9327
reg(0x00F2) 00 18 A3 12 02 B2 12 FF 10 00 00 00	Adjust Control 2
reg(0x00F6) 00 54 80 66	Interface Control
```

From the output of 0x00D3, you can see that the controller is ILI9486.

