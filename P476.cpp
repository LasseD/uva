#include <iostream>
#include <stdio.h>

struct Rect {
  double xMin, yMin, xMax, yMax;
};

bool is9999dot9(double d) {
  return 9999.88889 < d && 9999.99999 > d;
}

bool end(double x, double y) {
  return is9999dot9(x) && is9999dot9(y);
}

int main() {
  Rect rects[10];
  int numRects = 0;

  while(true) {
    char sym;
    std::cin >> sym;
    if(sym == '*')
      break;
    std::cin >> rects[numRects].xMin >> rects[numRects].yMax >> rects[numRects].xMax >> rects[numRects].yMin;
    ++numRects;
  }
  double x, y;
  for(int point = 0; true; ++point) {
    std::cin >> x >> y;
    if(end(x,y))
      return 0;
    bool any = false;
    for(int i = 0; i < numRects; ++i) {
      Rect &r = rects[i];
      if(r.xMin < x && r.xMax > x && r.yMin < y && r.yMax > y) {
	printf("Point %d is contained in figure %d\n", point+1, i+1);
	any = true;
      }
    }
    if(!any)
      printf("Point %d is not contained in any figure\n", point+1);
  }
}
