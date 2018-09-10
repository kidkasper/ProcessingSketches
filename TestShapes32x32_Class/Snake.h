/* Snake.h
 *  
 */ 

 #ifndef Snake_h
 #define Snake_h

 #include "Arduino.h"
 
#include <RGBmatrixPanel.h>

 class Snake
 {
    public:
      Snake(int x, int y, int startHue);
      void UpdateSnake();
      int NewDir(int oldDir);
      //void DrawThis();
      void Reset();
      int x[10];
      int y[10];
      int hue;
      int dir;
      int currentLength;
    private:
      int snakeSize;
      
      
      
      int sat;
      int dim;
      int dirX[8] = {1,1,0,-1,-1,-1,0,1};
      int dirY[8] = {0,1,1,1,0,-1,-1,-1};
      int vel;
 };
 
#endif
