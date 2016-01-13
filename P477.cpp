#include <iostream>
#include <stdio.h>

struct Figure {
  bool isCircle;
  double xMin, yMin, xMax, yMax, radius;
};

bool is9999dot9(double d) {
  return 9999.88889 < d && 9999.99999 > d;
}

bool end(double x, double y) {
  return is9999dot9(x) && is9999dot9(y);
}

bool inFigure(double x, double y, const Figure &fig) {
  if(fig.isCircle) {
    double dx = x-fig.xMin;
    double dy = y-fig.yMin;
    return dx*dx+dy*dy < fig.radius*fig.radius;
  }
  else {
    return fig.xMin < x && fig.xMax > x && fig.yMin < y && fig.yMax > y;
  }
}

int main() {
  Figure figures[10];
  int numFigures = 0;

  while(true) {
    char sym;
    std::cin >> sym;
    if(sym == '*')
      break;
    if(sym == 'r') {
      std::cin >> figures[numFigures].xMin >> figures[numFigures].yMax >> figures[numFigures].xMax >> figures[numFigures].yMin;
      figures[numFigures].isCircle = false;
    }
    else {
      std::cin >> figures[numFigures].xMin >> figures[numFigures].yMin >> figures[numFigures].radius;
      figures[numFigures].isCircle = true;
    }
    ++numFigures;
  }
  double x, y;
  for(int point = 0; true; ++point) {
    std::cin >> x >> y;
    if(end(x,y))
      return 0;
    bool any = false;
    for(int i = 0; i < numFigures; ++i) {
      if(inFigure(x, y, figures[i])) {
	printf("Point %d is contained in figure %d\n", point+1, i+1);
	any = true;
      }
    }
    if(!any)
      printf("Point %d is not contained in any figure\n", point+1);
  }
}
