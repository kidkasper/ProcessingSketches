// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <RGBmatrixPanel.h>
#include "Snake.h"

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

//Snake snake(16,16, 128);
Snake snake[3] = {Snake(12+round(random(8)),12+round(random(8)),round(random(255))),
Snake(12+round(random(8)),12+round(random(8)),round(random(255))),
Snake(12+round(random(8)),12+round(random(8)),round(random(255)))};

int dim = 31;
int hue = round(random(255));

void DrawSnake(int x1, int y1, int x2, int y2, int hsv, int sat) {
  //Simple mirror
  matrix.drawLine(x1, y1, x2, y2, matrix.ColorHSV(hsv, sat, 128, 1));
  matrix.drawLine(dim-x1, y1, dim-x2, y2, matrix.ColorHSV(hsv, sat, 128, 1));
  matrix.drawLine(x1, dim-y1, x2, dim-y2, matrix.ColorHSV(hsv, sat, 128, 1));
  matrix.drawLine(dim-x1, dim-y1, dim-x2, dim-y2, matrix.ColorHSV(hsv, sat, 128, 1));

  //8 way mirror
  matrix.drawLine(y1, x1, y2, x2, matrix.ColorHSV(hsv, sat, 128, 1));
  matrix.drawLine(dim-y1, x1, dim-y2, x2, matrix.ColorHSV(hsv, sat, 128, 1));
  matrix.drawLine(y1, dim-x1, y2, dim-x2, matrix.ColorHSV(hsv, sat, 128, 1));
  matrix.drawLine(dim-y1, dim-x1, dim-y2, dim-x2, matrix.ColorHSV(hsv, sat, 128, 1));
}

void setup() {
  
  Serial.begin(9600);
  matrix.begin();

  

}

void loop() {
  //Serial.print(dir1);
  for (int i = 0; i < 3; i++)
  {
    snake[i].UpdateSnake();
    for (int j = 0; j < snake[i].currentLength-1; i++) {
      DrawSnake(snake[i].x[j], snake[i].y[j], snake[i].x[j+1], snake[i].y[j+1], hue+i*96, 255);
    }
    Serial.print(snake[i].hue); 
    Serial.print("\n");

    if (snake[i].x[0] < 0 || snake[i].x[0] > dim || snake[i].y[0] < 0 || snake[i].y[0] > dim) {
      snake[i].Reset();
    }  
  }
  

  //Serial.print(snake.dir);
  //Serial.print(" x: " + snake.x[0]);
  //Serial.print(" y: " + snake.y[0]);
  
  //sat = max(sat%255 + 200,220);
  delay(25);
  matrix.fillScreen(matrix.Color333(0,0,0));
  hue += 12;
  // Do nothing -- image doesn't change
}




