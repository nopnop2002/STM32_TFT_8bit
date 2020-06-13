// adapted from LCD_ID_Reader from http://misc.ws/lcd_information
// controllers either read as 16-bit or as a sequence of 8-bit values

#define LCD_RST PB7
#define LCD_CS PB6
#define LCD_RS PB5
#define LCD_WR PB4
#define LCD_RD PB3

#define LCD_D0 PA0
#define LCD_D1 PA1
#define LCD_D2 PA2
#define LCD_D3 PA3
#define LCD_D4 PA4
#define LCD_D5 PA5
#define LCD_D6 PA6
#define LCD_D7 PA7

void setup()
{
    Serial.begin(9600);
    while (!Serial) ;
    Serial.println("Read Registers on MCUFRIEND UNO shield");
    Serial.println("controllers either read as single 16-bit");
    Serial.println("e.g. the ID is at readReg(0)");
    Serial.println("or as a sequence of 8-bit values");
    Serial.println("in special locations (first is dummy)");
    Serial.println("");
    lcdInit();
    lcdReset();      //ensures that controller is in default state
//    for (uint16_t i = 0; i < 256; i++) readReg(i, 7, "f.k"); 
    readReg(0x00, 2, "ID: ILI9320, ILI9325, ILI9335, ...");
    readReg(0x04, 4, "Manufacturer ID");
    readReg(0x09, 5, "Status Register");
    readReg(0x0A, 2, "Get Powsr Mode");
    readReg(0x0C, 2, "Get Pixel Format");
    readReg(0x61, 2, "RDID1 HX8347-G");
    readReg(0x62, 2, "RDID2 HX8347-G");
    readReg(0x63, 2, "RDID3 HX8347-G");
    readReg(0x64, 2, "RDID1 HX8347-A");
    readReg(0x65, 2, "RDID2 HX8347-A");
    readReg(0x66, 2, "RDID3 HX8347-A");
    readReg(0x67, 2, "RDID Himax HX8347-A");
    readReg(0x70, 2, "Panel Himax HX8347-A");
    readReg(0xA1, 5, "RD_DDB SSD1963");
    readReg(0xB0, 2, "RGB Interface Signal Control");
    readReg(0xB4, 2, "Inversion Control");
    readReg(0xB6, 5, "Display Control");
    readReg(0xB7, 2, "Entry Mode Set");
    readReg(0xBF, 6, "ILI9481, HX8357-B");
    readReg(0xC0, 9, "Panel Control");
    readReg(0xC8, 13, "GAMMA");
    readReg(0xCC, 2, "Panel Control");
    readReg(0xD0, 3, "Power Control");
    readReg(0xD2, 5, "NVM Read");
    readReg(0xD3, 4, "ILI9341, ILI9488");
    readReg(0xDA, 2, "RDID1");
    readReg(0xDB, 2, "RDID2");
    readReg(0xDC, 2, "RDID3");
    readReg(0xE0, 16, "GAMMA-P");
    readReg(0xE1, 16, "GAMMA-N");
    readReg(0xEF, 6, "ILI9327");
    readReg(0xF2, 12, "Adjust Control 2");
    readReg(0xF6, 4, "Interface Control");
}

void loop() 
{
    // put your main code here, to run repeatedly:

}

void printhex(uint8_t val)
{
    if (val < 0x10) Serial.print("0");
    Serial.print(val, HEX);
}

void readReg(uint16_t reg, uint8_t n, const char *msg)
{
    uint8_t val8;
    lcdReset();
    lcdSetWriteDir();
    lcdWriteCommand(0xB0);     //Command Access Protect
    lcdWriteData(0x00);        //looks wrong
/*
    lcdWriteCommand(0xF6);
    lcdWriteData(0x01);
    lcdWriteData(0x01);
    lcdWriteData(0x03);
*/
    lcdWriteCommand(reg);
    Serial.print("reg(0x");
    printhex(reg >> 8);
    printhex(reg);
    Serial.print(")");
    lcdSetReadDir();
    while (n--) {
        val8 = lcdReadData8();
        Serial.print(" ");
        printhex(val8);
    }
    lcdSetWriteDir();
    Serial.print("\t");
    Serial.println(msg);
}

void lcdInit()
{
    pinMode(LCD_CS, OUTPUT);
    digitalWrite(LCD_CS, HIGH);
    pinMode(LCD_RS, OUTPUT);
    digitalWrite(LCD_RS, HIGH);
    pinMode(LCD_WR, OUTPUT);
    digitalWrite(LCD_WR, HIGH);
    pinMode(LCD_RD, OUTPUT);
    digitalWrite(LCD_RD, HIGH);
    pinMode(LCD_RST, OUTPUT);
    digitalWrite(LCD_RST, HIGH);
}

void lcdReset()
{
    digitalWrite(LCD_RST, LOW);
    delay(2);
    digitalWrite(LCD_RST, HIGH);
    delay(10);             //allow controller to re-start
}

void lcdWrite8(uint16_t data)
{
    digitalWrite(LCD_D0, data & 1);
    digitalWrite(LCD_D1, (data & 2) >> 1);
    digitalWrite(LCD_D2, (data & 4) >> 2);
    digitalWrite(LCD_D3, (data & 8) >> 3);
    digitalWrite(LCD_D4, (data & 16) >> 4);
    digitalWrite(LCD_D5, (data & 32) >> 5);
    digitalWrite(LCD_D6, (data & 64) >> 6);
    digitalWrite(LCD_D7, (data & 128) >> 7);
}

uint16_t lcdRead8()
{
    uint16_t result = digitalRead(LCD_D7);
    result <<= 1;
    result |= digitalRead(LCD_D6);
    result <<= 1;
    result |= digitalRead(LCD_D5);
    result <<= 1;
    result |= digitalRead(LCD_D4);
    result <<= 1;
    result |= digitalRead(LCD_D3);
    result <<= 1;
    result |= digitalRead(LCD_D2);
    result <<= 1;
    result |= digitalRead(LCD_D1);
    result <<= 1;
    result |= digitalRead(LCD_D0);

    return result;
}

void lcdSetWriteDir()
{
    pinMode(LCD_D0, OUTPUT);
    pinMode(LCD_D1, OUTPUT);
    pinMode(LCD_D2, OUTPUT);
    pinMode(LCD_D3, OUTPUT);
    pinMode(LCD_D4, OUTPUT);
    pinMode(LCD_D5, OUTPUT);
    pinMode(LCD_D6, OUTPUT);
    pinMode(LCD_D7, OUTPUT);
}


void lcdSetReadDir()
{
    pinMode(LCD_D0, INPUT);
    pinMode(LCD_D1, INPUT);
    pinMode(LCD_D2, INPUT);
    pinMode(LCD_D3, INPUT);
    pinMode(LCD_D4, INPUT);
    pinMode(LCD_D5, INPUT);
    pinMode(LCD_D6, INPUT);
    pinMode(LCD_D7, INPUT);
}

void lcdWriteData(uint16_t data)
{
    lcdSetWriteDir();
    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_RS, HIGH);
    digitalWrite(LCD_RD, HIGH);
    digitalWrite(LCD_WR, HIGH);

    lcdWrite8(data >> 8);

    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);

    lcdWrite8(data);

    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);

    digitalWrite(LCD_CS, HIGH);
}

void lcdWriteCommand(uint16_t command)
{
    lcdSetWriteDir();
    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_RS, LOW);
    digitalWrite(LCD_RD, HIGH);
    digitalWrite(LCD_WR, HIGH);
    lcdWrite8(command >> 8);
    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);
    lcdWrite8(command);
    digitalWrite(LCD_WR, LOW);
    delayMicroseconds(10);
    digitalWrite(LCD_WR, HIGH);
    digitalWrite(LCD_CS, HIGH);
}

uint8_t lcdReadData8()
{
    uint8_t result;
    lcdSetReadDir();
    digitalWrite(LCD_CS, LOW);
    digitalWrite(LCD_RS, HIGH);
    digitalWrite(LCD_RD, HIGH);
    digitalWrite(LCD_WR, HIGH);

    digitalWrite(LCD_RD, LOW);
    delayMicroseconds(10);
    result = lcdRead8();
    digitalWrite(LCD_RD, HIGH);

    delayMicroseconds(10);

    return result;
}


uint16_t lcdReadData16()
{
    uint16_t result;
    result = lcdReadData8() << 8;
    result |= lcdReadData8();
    return result;
}


void lcdWriteRegister(uint16_t addr, uint16_t data)
{
    lcdWriteCommand(addr);
    lcdWriteData(data);
}
