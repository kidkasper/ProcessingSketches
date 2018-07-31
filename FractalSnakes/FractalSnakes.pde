int  cellsize = 20;
int gridsize = 20;
int size = 0;

int count = 1;

Snake[] snakes;

void setup() {
  background(40);
  colorMode(HSB,360,100,100,100);    
  init();
}

void init() {  
  size = gridsize * cellsize;

  int padding = 30;
  int border = 50;

  size((size * count) + ((count - 1) * padding) + border * 2, (size * count) + ((count - 1) * padding) + border * 2);

  noFill();
  strokeWeight(cellsize / 2);
  strokeCap(ROUND);
  frameRate(25);

  for (int y = 0; y < count; y++)
    for (int x = 0; x < count; x++)
      for (int i = 0; i < 3; i++)
        snakes.push(new Snake(x * size + x * padding + border, y * size + y * padding + border));
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
  Snake(int x, int y){
    this.dead = false;
    this.x = x;
    this.y = y;
  }
  
  int segCount = round(random(2, 10));
  PVector[] segs;

  PVector dir = PVector.fromAngle(floor(random(4)) * (TWO_PI / 4)).mult(cellsize);

  //var size = gridsize*cellsize;

  PVector pos = new PVector(Math.ceil(random(size) / cellsize) * cellsize, Math.ceil(random(size) / cellsize) * cellsize);
  
  PVector newPos = new PVector(0, 0);

  int frames = 0;

  segs.push(pos);

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

    segs.unshift(newPos);
    pos = newPos;

    if (segs.length > segCount) segs.pop();
  };

  color c = color(random(360), random(10, 70), 100);  //Needs to be changed to HSB

  void draw() {
    stroke(c);
    Boolean dead = true;

    for (int i = 0; i < segs.length - 1; i++) {
      PVector s = segs[i];
      PVector e = segs[i + 1];

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
      }
    }

    frames++;

    stroke(0, 0, 75);
    noFill();
    rect(this.x, this.y, size, size, 5, 5, 5, 5);
  };
}