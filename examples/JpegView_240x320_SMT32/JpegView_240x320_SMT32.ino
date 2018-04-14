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
#include <SdFat.h>  // https://github.com/greiman/SdFat
#include <JPEGDecoder.h>  // https://github.com/nopnop2002/STM32_JPEGDecorder

STM32_TFT_8bit tft;

uint32_t ID;

// Use second SPI port
SdFat SD(2);
//SdFatEX SD(2);
const uint8_t SD_CS = PB12;   // chip select for sd2

//------------------------------------------------------------------------------
// print error msg, any SD error codes, and halt.
// store messages in flash
#define errorExit(msg) errorHalt(F(msg))
#define initError(msg) initErrorHalt(F(msg))
//------------------------------------------------------------------------------


void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("STM32_TFT_8bit Test!"); 

  ID = tft.readID();
  Serial.print("Device ID: 0x"); Serial.println(ID, HEX);
  tft.begin(ID);

  uint32_t width = tft.width();
  Serial.print("Width: "); Serial.println(width);
  uint32_t height = tft.height();
  Serial.print("Height: "); Serial.println(height);
  

  // initialize the second card
  //if (!SD.begin(SD2_CS, SD_SCK_MHZ(18))) {
  if (!SD.begin(SD_CS)) {
    SD.initError("sd:");
  }

  // Show JPEG file list on console
  showJpegFileList();
}


void loop(void) {
  static long fno = 0;
  // Draw a jpeg image
  tft.fillScreen(random(0x10000));
  if ( (fno % 6) == 0) drawFSJpeg("healsky3.jpg", 0, 0);
  if ( (fno % 6) == 1) drawFSJpeg("selfie.jpg", 0, 0);
  if ( (fno % 6) == 2) drawFSJpeg("sunrise.jpg", 0, 0);
  if ( (fno % 6) == 3) drawFSJpeg("tile1920.jpg", 0, 0);
  if ( (fno % 6) == 4) drawFSJpeg("tree.jpg", 0, 0);
  if ( (fno % 6) == 5) drawFSJpeg("JpegView.jpg", 0, 0);
  fno++;
  delay(5000);
}

