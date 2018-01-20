/*
 An example analogue clock using a TFT LCD screen to show the time
 use of some of the drawing commands with the Adafruit_GFX library.
 For a more accurate clock, it would be better to use the RTC library.
 But this is just a demo. 
 
 Gilchrist 6/2/2014 1.0
 Updated by Alan Senior 18/1/2015
 Updated by nopnop2002 5/1/2018
 */


#include <Adafruit_GFX.h>
#include "STM32_TFT_8bit.h"

STM32_TFT_8bit tft;

float sx = 0, sy = 1, mx = 1, my = 0, hx = -1, hy = 0;    // Saved H, M, S x & y multipliers
float sdeg=0, mdeg=0, hdeg=0;
uint16_t osx=120, osy=120, omx=120, omy=120, ohx=120, ohy=120;  // Saved H, M, S x & y coords
uint16_t x00=0, x11=0, y00=0, y11=0;
uint32_t targetTime = 0;                    // for next 1 second timeout
uint8_t hh,mm,ss;
boolean initial = 1;

void setup(void) {
  delay(1000);
  Serial.begin(9600);
  hh=conv2d(__TIME__);
  mm=conv2d(__TIME__+3);
  ss=conv2d(__TIME__+6);  // Get H, M, S from compile time
  uint16_t ID = tft.readID();
  Serial.print("Device ID: 0x"); Serial.println(ID, HEX);
  tft.begin(ID);
  uint16_t wid = tft.width();
  uint16_t ht = tft.height();
  Serial.println("width=" + String(wid) + " height=" + String(ht));

  if (wid < ht) {
    tft.setRotation(0);
  } else {
    tft.setRotation(1);
  }
  tft.fillScreen(GRAY);
  tft.setTextColor(WHITE, GRAY);  // Adding a background colour erases previous text automatically
  
  // Draw clock face
  tft.fillCircle(120, 120, 118, GREEN);
  tft.fillCircle(120, 120, 110, BLACK);

  // Draw 12 lines
  for(int i = 0; i<360; i+= 30) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x00 = sx*114+120;
    y00 = sy*114+120;
    x11 = sx*100+120;
    y11 = sy*100+120;

    tft.drawLine(x00, y00, x11, y11, GREEN);
  }

  // Draw 60 dots
  for(int i = 0; i<360; i+= 6) {
    sx = cos((i-90)*0.0174532925);
    sy = sin((i-90)*0.0174532925);
    x00 = sx*102+120;
    y00 = sy*102+120;
    // Draw minute markers
    tft.drawPixel(x00, y00, WHITE);
    
    // Draw main quadrant dots
    if(i==0 || i==180) tft.fillCircle(x00, y00, 2, WHITE);
    if(i==90 || i==270) tft.fillCircle(x00, y00, 2, WHITE);
  }

  tft.fillCircle(120, 121, 3, WHITE);
  tft.setCursor(20, 260);
  tft.setTextSize(3);
  tft.println(__DATE__);
  targetTime = millis() + 1000; 
}

void loop() {

  if (targetTime < millis()) {
    targetTime = millis()+1000;
    ss++;              // Advance second
    if (ss==60) {
      ss=0;
      mm++;            // Advance minute
      if(mm>59) {
        mm=0;
        hh++;          // Advance hour
        if (hh>23) {
          hh=0;
        }
      }
    }
    #ifdef _DEBUG_
    Serial.print("hh=");
    Serial.print(hh);
    Serial.print(" mm=");
    Serial.print(mm);
    Serial.print(" ss=");
    Serial.println(ss);
    #endif
    
    // Pre-compute hand degrees, x & y coords for a fast screen update
    sdeg = ss*6;                  // 0-59 -> 0-354
    mdeg = mm*6+sdeg*0.01666667;  // 0-59 -> 0-360 - includes seconds
    hdeg = hh*30+mdeg*0.0833333;  // 0-11 -> 0-360 - includes minutes and seconds
    hx = cos((hdeg-90)*0.0174532925);    
    hy = sin((hdeg-90)*0.0174532925);
    mx = cos((mdeg-90)*0.0174532925);    
    my = sin((mdeg-90)*0.0174532925);
    sx = cos((sdeg-90)*0.0174532925);    
    sy = sin((sdeg-90)*0.0174532925);

    if (ss==0 || initial) {
      initial = 0;
      // Erase hour and minute hand positions every minute
      tft.drawLine(ohx, ohy, 120, 121, BLACK);
      ohx = hx*62+121;    
      ohy = hy*62+121;
      tft.drawLine(omx, omy, 120, 121, BLACK);
      omx = mx*84+120;    
      omy = my*84+121;
    }

      // Redraw new hand positions, hour and minute hands not erased here to avoid flicker
      tft.drawLine(osx, osy, 120, 121, BLACK);
      osx = sx*90+121;    
      osy = sy*90+121;
      tft.drawLine(osx, osy, 120, 121, RED);
      tft.drawLine(ohx, ohy, 120, 121, WHITE);
      tft.drawLine(omx, omy, 120, 121, WHITE);
      tft.drawLine(osx, osy, 120, 121, RED);

    tft.fillCircle(120, 121, 3, RED);
  }
}

static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

