/*
 * 8bit TFT Library for STM32F103
 * based on MCUFRIEND_kbv.cpp by David Prentice
 * https://github.com/prenticedavid/MCUFRIEND_kbv
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Adafruit_GFX.h>
#include "STM32_TFT_8bit.h"

STM32_TFT_8bit tft;

void setup(void) {
    delay(1000);
    Serial.begin(9600);

    uint16_t ID = tft.readID();
    Serial.println("ID = 0x" + String(ID,HEX));
    tft.begin(ID);
}


void loop(void) {
    uint8_t aspect;
    uint16_t pixel;
    const char *aspectname[] = {
        "PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV"
    };
    const char *colorname[] = { "BLUE", "GREEN", "RED", "GRAY" };
    uint16_t colormask[] = { 0x001F, 0x07E0, 0xF800, 0xFFFF };
    uint16_t dx, rgb, n, wid, ht, msgline;
    tft.setRotation(0);
    if (tft.height() > 64) {
        for (uint8_t cnt = 0; cnt < 4; cnt++) {
            aspect = (cnt + 0) & 3;
            tft.setRotation(aspect);
            wid = tft.width();
            ht = tft.height();
            Serial.println("aspect=" + String(aspect));
            Serial.println("width=" + String(wid) + " height=" + String(ht));
            msgline = (ht > 160) ? 200 : 112;
            testText();
            
            // Show COLOR GRADES
            dx = wid / 32;
            for (n = 0; n < 32; n++) {
                rgb = n * 8;
                rgb = tft.color565(rgb, rgb, rgb);
                tft.fillRect(n * dx, 48, dx, 63, rgb & colormask[aspect]);
            }
            tft.drawRect(0, 48 + 63, wid, 1, WHITE);
            tft.setTextSize(2);
            tft.setTextColor(colormask[aspect], BLACK);
            tft.setCursor(0, 72);
            tft.print(colorname[aspect]);
            tft.setTextColor(WHITE);
            tft.println(" COLOR GRADES");
            tft.setTextColor(WHITE, BLACK);
            printmsg(184, aspectname[aspect]);
            delay(1000);
            tft.drawPixel(0, 0, YELLOW);
            pixel = tft.readPixel(0, 0);
            tft.setTextSize((ht > 160) ? 2 : 1); //for messages

            // Show penguin icon
            extern const uint8_t penguin[];
            tft.setAddrWindow(wid - 40 - 40, 20 + 0, wid - 1 - 40, 20 + 39);
            tft.pushColors8((uint8_t *)penguin, 1600, 1);

            // Scroll Screen
            tft.setAddrWindow(0, 0, wid - 1, ht - 1);
            if (aspect & 1) tft.drawRect(wid - 1, 0, 1, ht, WHITE);
            else tft.drawRect(0, ht - 1, wid, 1, WHITE);
            printmsg(msgline, "VERTICAL SCROLL UP");
            uint16_t maxscroll;
            if (tft.getRotation() & 1) maxscroll = wid;
            else maxscroll = ht;
            int step = -1;
            if ( wid < ht ) step = 1;

            // Scroll Up
            for (int16_t i = 1; i <= maxscroll; i++) {
                tft.vertScroll(0, maxscroll, i * step);
                delay(10);
            }
            delay(1000);

            // Scroll Down
            printmsg(msgline, "VERTICAL SCROLL DN");
            for (int16_t i = 1; i <= maxscroll; i++) {
                tft.vertScroll(0, maxscroll, (0 - i) * step);
                delay(10);
            }
			      tft.vertScroll(0, maxscroll, 0);
            printmsg(msgline, "SCROLL DISABLED");

            // Scroll COLOR GRADES
            delay(1000);
            if ((aspect & 1) == 0) { //Portrait
                int stline;
                stline = 128;
                step = -1;
                if (wid < ht) {
                  stline = 48;
                  step = 1;
                }
                tft.setTextColor(BLUE, BLACK);
                printmsg(msgline, "ONLY THE COLOR BAND");
                for (int16_t i = 1; i <= 64; i++) {
                    tft.vertScroll(stline, 64, i * step);
                    delay(20);
                }
                delay(1000);
                for (int16_t i = 1; i <= 64; i++) {
                    tft.vertScroll(stline, 64, (0 - i) * step);
                    delay(20);
                }
                delay(1000);

#if 0
                if ( wid < ht ) {
                  stline = 48;
                  for (int16_t i = 1; i <= 64; i++) {
                      tft.vertScroll(stline, 64, i);
                      delay(20);
                  }
                  delay(1000);
                  for (int16_t i = 1; i <= 64; i++) {
                      tft.vertScroll(stline, 64, 0 - i);
                      delay(20);
                  }
                  delay(1000);
                } else {
                  stline = 128;
                  for (int16_t i = 1; i <= 64; i++) {
                      tft.vertScroll(stline, 64, 0 - i);
                      delay(20);
                  }
                  delay(1000);
                  for (int16_t i = 1; i <= 64; i++) {
                      tft.vertScroll(stline, 64, i);
                      delay(20);
                  }
                  delay(1000);
                }
#endif                  
            }

            printmsg(msgline, "INVERT DISPLAY");
            tft.invertDisplay(true);
            delay(3000);
            printmsg(msgline, "NORMAL DISPLAY");
            tft.invertDisplay(false);
            delay(3000);
        }
    }
}

void testText() {
    tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE);  tft.setTextSize(1);
    tft.println("Hello World!");
    tft.setTextColor(YELLOW); tft.setTextSize(2);
    tft.println(123.45);
    tft.setTextColor(RED);    tft.setTextSize(3);
    tft.println(0xDEADBEEF, HEX);
    tft.println();
    tft.setTextColor(GREEN);
    tft.setTextSize(5);
    tft.println("Groop");
    tft.setTextSize(2);
    tft.println("I implore thee,");
    tft.setTextSize(1);
    tft.println("my foonting turlingdromes.");
    tft.println("And hooptiously drangle me");
    tft.println("with crinkly bindlewurdles,");
    tft.println("Or I will rend thee");
    tft.println("in the gobberwarts");
    tft.println("with my blurglecruncheon,");
    tft.println("see if I don't!");
}

void printmsg(int row, const char *msg)
{
    static char primary_msg[64];
    
    if (strlen(primary_msg)) {
      tft.setTextColor(BLACK, BLACK);
      tft.setCursor(0, row);
      tft.println(primary_msg);
    }
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(0, row);
    tft.println(msg);
    strcpy(primary_msg,msg);
}



