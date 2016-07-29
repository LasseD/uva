#include <iostream>
#include <stdio.h>

typedef long Cube;
typedef int Color;

#define RED 0
#define GREEN 1
#define BLUE 2

#define UP 0
#define DOWN 5
#define LEFT 2
#define RIGHT 3
#define TOP 1
#define BOTTOM 4

Cube buildCube(Color up, Color down, Color left, Color right, Color top, Color bottom) {
  return + (up << 2*UP) + (down << 2*DOWN) + (left << 2*LEFT) + (right << 2*RIGHT) + (top << 2*TOP) + (bottom << 2*BOTTOM);
}
Color getColor(Cube c, int side) {
  return (c >> 2*side) & 3;
}
char colorToChar(Color c) {
  switch(c) {
  case RED:
    return 'r';
  case BLUE:
    return 'b';
  default:
    return 'g';
  }
}
void print(Cube c) {
  for(int i = 0; i < 6; ++i) {
    std::cout << colorToChar(getColor(c, i));
  }
}

Cube up(Cube c) {
  Color up = getColor(c, UP);
  Color down = getColor(c, DOWN);
  Color left = getColor(c, LEFT);
  Color right = getColor(c, RIGHT);
  Color top = getColor(c, TOP);
  Color bottom = getColor(c, BOTTOM);

  return buildCube(top, bottom, left, right, down, up);
}
Cube right(Cube c) {
  Color up = getColor(c, UP);
  Color down = getColor(c, DOWN);
  Color left = getColor(c, LEFT);
  Color right = getColor(c, RIGHT);
  Color top = getColor(c, TOP);
  Color bottom = getColor(c, BOTTOM);

  return buildCube(up, down, bottom, top, left, right);
}
Cube left(Cube c) {
  Color up = getColor(c, UP);
  Color down = getColor(c, DOWN);
  Color left = getColor(c, LEFT);
  Color right = getColor(c, RIGHT);
  Color top = getColor(c, TOP);
  Color bottom = getColor(c, BOTTOM);

  return buildCube(up, down, top, bottom, right, left);
}
Cube rot(Cube c) {
  Color up = getColor(c, UP);
  Color down = getColor(c, DOWN);
  Color left = getColor(c, LEFT);
  Color right = getColor(c, RIGHT);
  Color top = getColor(c, TOP);
  Color bottom = getColor(c, BOTTOM);

  return buildCube(left, right, down, up, top, bottom);
}
bool isRotSame(Cube c, Cube turning) {
  if(c == turning)
    return true;
  for(int i = 0; i < 3; ++i) {
    turning = rot(turning);
    if(c == turning)
      return true;
  }
  return false;
}
bool isSame(Cube c, Cube turning) {
  for(int i = 0; i < 4; ++i) {
    if(isRotSame(c, turning))
      return true;
    turning = up(turning);
  }
  return isRotSame(c, left(turning)) || isRotSame(c, right(turning));
}

Color getColor(char c) {
  switch(c) {
  case 'r':
    return RED;
  case 'g':
    return GREEN;
  default:
    return BLUE;
  }
}
Cube parseCube(char *w) {
  return buildCube(getColor(w[UP]),getColor(w[DOWN]),getColor(w[LEFT]),getColor(w[RIGHT]),getColor(w[TOP]),getColor(w[BOTTOM]));
}

int main() {
  char w[39];
  while(gets(w)) {
    Cube c1 = parseCube(w);
    /*std::cerr << c1;
    for(int i = 0; i < 4; ++i) {
      c1 = up(c1);
      std::cerr <<"->"<< c1;
    }
    std::cerr << std::endl;
    std::cerr << c1;
    for(int i = 0; i < 4; ++i) {
      c1 = right(c1);
      std::cerr <<"->"<< c1;
    }
    std::cerr << std::endl;
    std::cerr << c1;
    for(int i = 0; i < 4; ++i) {
      c1 = left(c1);
      std::cerr <<"->"<< c1;
    }
    std::cerr << std::endl;
    std::cerr << c1;
    for(int i = 0; i < 4; ++i) {
      c1 = rot(c1);
      std::cerr <<"->"<< c1;
    }
    std::cerr << std::endl;
    return 0;//*/
    Cube c2 = parseCube(&w[6]);
    if(isSame(c1, c2))
      std::cout << "TRUE" << std::endl;
    else
      std::cout << "FALSE" << std::endl;
  }
  return 0;
}
