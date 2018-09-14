#include  "Arduino.h"
#include "Snake.h"
#include <RGBmatrixPanel.h>

Snake::Snake(int x1, int y1, int startHue) 
{
  snakeSize = 10;
  currentLength = 1;
  x[0] = x1;
  y[0] = y1;
  sat = 255;
  hue = startHue; 
  dir = round(random(8));
  dim = 31;
  vel = 2;
}

int Snake::NewDir(int oldDir) {
  int change = round(random(0,2))-1;
  //Serial.print(change);
  return ((oldDir+change+8)%8);
}

void Snake::UpdateSnake()
{
  // increment lenth
  if (currentLength < snakeSize) {
    currentLength++;
  }
  
  // shuffle position array 
  for (int i = currentLength-1; i > 0; i--) {
    x[i+1] = x[i];
    y[i+1] = y[i];
  }

  //calculate new psotion
  x[0] = x[1]+ dirX[dir]*vel;
  y[0] = y[1]+ dirY[dir]*vel;
  
   //Serial.print(y[1]);
  //generate new direction
  dir = NewDir(dir);

  //increment hue
  hue += 10;
  hue = hue%256;
}

void Snake::Reset()
{
  currentLength = 2;
  x[0] = round(16 + random(-4,4));
  y[0] = round(16 + random(-4,4));
  x[1] = x[0];
  y[1] = y[0];
  hue = round(random(255)); 

}

