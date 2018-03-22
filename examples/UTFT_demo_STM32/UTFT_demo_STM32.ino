// Demo based on:
// UTFT_Demo_320x240 by Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//

#include <Adafruit_GFX.h>
#include "STM32_TFT_8bit.h"

STM32_TFT_8bit myGLCD;


#define TFT_GREY   GRAY
#define TFT_BLACK  BLACK
#define TFT_RED    RED
#define TFT_CYAN   CYAN
#define TFT_YELLOW YELLOW
#define TFT_BLUE   BLUE

int sbuf[318];
int cbuf[318];

void setup()
{
  Serial.begin(9600);
  uint32_t ID = myGLCD.readID();
  Serial.print("Device ID: 0x"); Serial.println(ID, HEX);
  myGLCD.begin(ID);

  uint32_t width = myGLCD.width();
  Serial.print("Width: "); Serial.println(width);
  uint32_t height = myGLCD.height();
  Serial.print("Height: "); Serial.println(height);

  int buf[318];

// Clear the screen and draw the frame
  myGLCD.setRotation(3);
  myGLCD.setFont();
  myGLCD.setTextSize(1);

  myGLCD.fillScreen(TFT_BLACK);
  myGLCD.fillRect(0, 0, 319, 14,TFT_RED);
  myGLCD.fillRect(0, 226, 319, 14,TFT_GREY);

  myGLCD.setTextColor(TFT_BLACK,TFT_RED);
  myGLCD.setCursor(100, 4);
  myGLCD.print("* STM32_TFT_8bit *");
  myGLCD.setTextColor(TFT_YELLOW,TFT_GREY);
  myGLCD.setCursor(100, 230);
  myGLCD.print("Adapted by nopnop2002");

  myGLCD.drawRect(0, 14, 319, 211, TFT_BLUE);

// Draw crosshairs
  myGLCD.drawLine(159, 15, 159, 224,TFT_BLUE);
  myGLCD.drawLine(1, 119, 318, 119,TFT_BLUE);
  for (int i=9; i<310; i+=10)
    myGLCD.drawLine(i, 117, i, 121,TFT_BLUE);
  for (int i=19; i<220; i+=10)
    myGLCD.drawLine(157, i, 161, i,TFT_BLUE);

// Draw sin-lines, cos-lines  
  myGLCD.setTextColor(TFT_CYAN);
  _drawString("Sin", 5, 15,2);
  for (int i=1; i<318; i=i+2)
  {
    sbuf[i-1] = 119+(sin(((i*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,sbuf[i-1],TFT_CYAN);
  }
  myGLCD.setTextColor(TFT_RED);
  _drawString("Cos", 5, 30,2);
  for (int i=1; i<318; i=i+2)
  {
    cbuf[i-1] = 119+(cos(((i*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,cbuf[i-1],TFT_YELLOW);
  }

}

void loop()
{
  static int delta = 0;

// Erase sin-lines, cos-lines
  for (int i=1; i<318; i=i+2)
  {
    myGLCD.drawPixel(i,sbuf[i-1],TFT_BLACK);
  }
  for (int i=1; i<318; i=i+2)
  {
    myGLCD.drawPixel(i,cbuf[i-1],TFT_BLACK);
  }

// Draw sin-lines, cos-lines  
  delta++;
  if (delta == 318) delta = 0;
  for (int i=1; i<318; i=i+2)
  {
    sbuf[i-1] = 119+(sin((((i+delta)*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,sbuf[i-1],TFT_CYAN);
  }
  for (int i=1; i<318; i=i+2)
  {
    cbuf[i-1] = 119+(cos((((i+delta)*1.13)*3.14)/180)*95);
    myGLCD.drawPixel(i,cbuf[i-1],TFT_YELLOW);
  }

  myGLCD.setTextColor(TFT_CYAN);
//  myGLCD.drawString("Sin", 5, 15,2);
  _drawString("Sin", 5, 15,2);
  myGLCD.setTextColor(TFT_YELLOW);
//  myGLCD.drawString("Cos", 5, 30,2);
  _drawString("Cos", 5, 30,2);
  myGLCD.drawLine(159, 15, 159, 224,TFT_BLUE);
  myGLCD.drawLine(1, 119, 318, 119,TFT_BLUE);
}

void _drawString(char *buf, int16_t x, int16_t y, int16_t size)
{
  myGLCD.setTextSize(size);
  myGLCD.setCursor(x, y);
  myGLCD.print(buf);
}
