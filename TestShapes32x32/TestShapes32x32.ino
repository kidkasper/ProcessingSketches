// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>

// Most of the signal pins are configurable, but the CLK pin has some
// special constraints.  On 8-bit AVR boards it must be on PORTB...
// Pin 8 works on the Arduino Uno & compatibles (e.g. Adafruit Metro),
// Pin 11 works on the Arduino Mega.  On 32-bit SAMD boards it must be
// on the same PORT as the RGB data pins (D2-D7)...
// Pin 8 works on the Adafruit Metro M0 or Arduino Zero,
// Pin A4 works on the Adafruit Metro M4 (if using the Adafruit RGB
// Matrix Shield, cut trace between CLK pads and run a wire to A4).

//#define CLK  8   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int x1, y1, x2, y2;
int hsv;

void setup() {

  matrix.begin();

  x1 = 16;
  y1 = 16;
  x2 = round(random(32));
  y2 = round(random(32));
  int hsv = 0;
  // whew!
}

void loop() {
  delay(20);
  matrix.drawLine(x1, y1, x2, y2, matrix.ColorHSV(hsv, 255, 128, 1));
  matrix.drawLine(31-x1, y1, 31-x2, y2, matrix.ColorHSV(hsv, 255, 128, 1));
  matrix.drawLine(x1, 31-y1, x2, 31-y2, matrix.ColorHSV(hsv, 255, 128, 1));
  matrix.drawLine(31-x1, 31-y1, 31-x2, 31-y2, matrix.ColorHSV(hsv, 255, 128, 1));
  x1 = x2;
  y1 = y2;
  x2 += round(random(4));
  y2 += round(random(4));
  x2 = x2%32;
  y2 = y2%32;
  hsv +=11; 
  //matrix.fillScreen(matrix.Color333(0,0,0));
  // Do nothing -- image doesn't change
}
