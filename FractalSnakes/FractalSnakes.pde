int  cellsize = 20;
int gridsize = 20;
int size = 0;

int count = 1;

Snake[] snakes;

void setup() {
  background(40);
  colorMode(HSB,360,100,100,100);    
  size = gridsize * cellsize;

  int padding = 30;
  int border = 50;
  int xres = (size * count) + ((count - 1) * padding) + border * 2;
  int yres = (size * count) + ((count - 1) * padding) + border * 2;

  size(500, 500);

  noFill();
  strokeWeight(cellsize / 2);
  strokeCap(ROUND);
  frameRate(25);
  
  snakes = new Snake[3];

  for (int y = 0; y < count; y++)
    for (int x = 0; x < count; x++)
      for (int i = 0; i < 3; i++)
      //snakes[i] = new Snake(250, 250);
      snakes[i] = new Snake(x * size + x * padding + border, y * size + y * padding + border);
}

void draw() {
  noStroke();
  fill(0,0,20,50);
  rect(0,0,width,height,30);
  
  for (int i = 0; i < snakes.length; i++) {
    snakes[i].update();
    snakes[i].draw();
    if (snakes[i].dead) snakes[i] = new Snake(snakes[i].x, snakes[i].y);
  }
}

class Snake {
  int x, y;
  boolean dead;
  PVector pos;
  ArrayList<PVector> segs = new ArrayList<PVector>();
  color c = color(random(360), random(10, 70), 100);  //Needs to be changed to HSB
  
  Snake(int x, int y){
    this.dead = false;
    this.x = x;
    this.y = y;
    pos = new PVector(ceil(random(size) / cellsize) * cellsize, ceil(random(size) / cellsize) * cellsize);
    segs.add(pos);
  }
  
  int segCount = round(random(2, 10));
 
  
  //PVector[] segs;

  PVector dir = PVector.fromAngle(floor(random(4)) * (TWO_PI / 4)).mult(cellsize);
  int size = gridsize*cellsize;
  PVector newPos = new PVector(0, 0);
  int frames = 0;
  
  //segs = (PVector[])append(segs,pos);

  void update() {
    if (random(1) < 0.3) {
      frames = 0;
      float rot = 0;
      while (rot == 0) {
        rot = round(random(-1, 1));
      }
      dir.rotate(TWO_PI / random(12) * rot);
    }

    //move
    newPos = PVector.add(pos, dir);

    //Add new element at start of array
    segs.add(0,newPos);
    pos = newPos;

    if (segs.size() > segCount) segs.remove(segs.size()-1);
  };

  

  void draw() {
    stroke(c);
    dead = true;

    for (int i = 0; i < segs.size() - 1; i++) {
      PVector s = segs.get(i);
      PVector e = segs.get(i + 1);

      if (s.x >= 0 && s.x <= size && s.y >= 0 && s.y <= size) {
        if (e.x >= 0 && e.x <= size && e.y >= 0 && e.y <= size) {

          line(s.x + this.x, s.y + this.y, e.x + this.x, e.y + this.y);
          line(s.y + this.x, s.x + this.y, e.y + this.x, e.x + this.y);

          line(size - s.x + this.x, s.y + this.y, size - e.x + this.x, e.y + this.y);
          line(size - s.y + this.x, s.x + this.y, size - e.y + this.x, e.x + this.y);

          line(s.x + this.x, size - s.y + this.y, e.x + this.x, size - e.y + this.y);
          line(s.y + this.x, size - s.x + this.y, e.y + this.x, size - e.x + this.y);

          line(size - s.x + this.x, size - s.y + this.y, size - e.x + this.x, size - e.y + this.y);
          line(size - s.y + this.x, size - s.x + this.y, size - e.y + this.x, size - e.x + this.y);

          //dead check
          this.dead = false;
        }
      } else {
         println("Dead"); 
      }
    }

    frames++;

    stroke(0, 0, 75);
    noFill();
    rect(this.x, this.y, size, size, 5, 5, 5, 5);
  };
}