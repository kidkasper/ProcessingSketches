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

int x1, y1, x2, y2, x3, y3, x4, y4;
int dir1, dir2;
int hsv;
int sat;

int dirX[8] = {1,1,0,-1,-1,-1,0,1};
int dirY[8] = {0,1,1,1,0,-1,-1,-1};

int dim = 31;
int vel = 2;

int NewDir(int oldDir) {
  return ((oldDir+round(random(-1,1))+8)%8);
}

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

  x1 = 16;
  y1 = 16;
  x2 = round(random(32));
  y2 = round(random(32));
  x3 = 16;
  y3 = 16;
  x4 = round(random(32));
  y4 = round(random(32));
  
  dir1 = round(random(8));
  dir2 = round(random(8));
  int hsv = 0;
  int sat = 255;
  // whew!
}

void loop() {
  dir1 = NewDir(dir1);
  Serial.print(dir1);
  x1 = x2;
  y1 = y2;
  //dir +=1;
  //dir = dir%8;
  x2 += vel*dirX[dir1];
  y2 += vel*dirY[dir1];

  dir2 = NewDir(dir2);
  Serial.print(dir2);
  x3 = x4;
  y3 = y4;
  //dir +=1;
  //dir = dir%8;
  x4 += vel*dirX[dir1];
  y4 += vel*dirY[dir1];
  
  DrawSnake(x1, y1, x2, y2, hsv, 255);
  DrawSnake(x3, y3, x4, y4, hsv+128, 255);

  //Boundary wraparound 
  if (0) {
    x2 = x2%32;
    y2 = y2%32;
  }

  if (x2 < 0 || x2 > dim || y2 < 0 || y2 > dim) {
    int newPosX = round(random(dim+1));
    int newPosY = round(random(dim+1));
    x1 = newPosX;
    y1 = newPosY;
    x2 = newPosX;
    y2 = newPosY;
  }

  if (x4 < 0 || x4 > dim || y4 < 0 || y4 > dim) {
    int newPosX = round(random(dim+1));
    int newPosY = round(random(dim+1));
    x3 = newPosX;
    y3 = newPosY;
    x4 = newPosX;
    y4 = newPosY;
  }
  
  hsv +=3; 
  
  //sat = max(sat%255 + 200,220);
  delay(25);
  matrix.fillScreen(matrix.Color333(0,0,0));
  // Do nothing -- image doesn't change
}




