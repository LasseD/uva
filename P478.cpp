#include <iostream>
#include <stdio.h>

#define CIRCLE 0
#define RECTANGLE 1
#define TRIANGLE 2
#define x first
#define y second

typedef std::pair<double,double> Point;

bool rightTurn(double diffX, double diffY, double x1, double y1, const Point &p) {
  return diffX*(p.y-y1) < diffY*(p.x-x1);
}
bool rightTurn(const Point &p1, const Point &p2, const Point &p) {
  return rightTurn(p2.x-p1.x, p2.y-p1.y, p2.x, p2.y, p);
}
bool colinear(double diffX, double diffY, double x1, double y1, const Point &p) {
  return diffX*(p.y-y1) == diffY*(p.x-x1);
}
bool colinear(const Point &p1, const Point &p2, const Point &p) {
  return colinear(p2.x-p1.x, p2.y-p1.y, p2.x, p2.y, p);
}

struct Figure {
  int type;
  Point p1, p2, p3;
  double radius;
};

bool is9999dot9(double d) {
  return 9999.88889 < d && 9999.99999 > d;
}
bool end(Point p) {
  return is9999dot9(p.x) && is9999dot9(p.y);
}

bool inFigure(Point p, const Figure &fig) {
  if(fig.type == CIRCLE) {
    double dx = p.x-fig.p1.x;
    double dy = p.y-fig.p1.y;
    return dx*dx+dy*dy < fig.radius*fig.radius;
  }
  else if(fig.type == RECTANGLE)
    return fig.p1.x < p.x && fig.p2.x > p.x && fig.p1.y < p.y && fig.p2.y > p.y;
  else
    return rightTurn(fig.p1, fig.p2, p) && rightTurn(fig.p2, fig.p3, p) && rightTurn(fig.p3, fig.p1, p);
}

int main() {
  Figure figures[10];
  int numFigures = 0;

  while(true) {
    char sym;
    std::cin >> sym;
    if(sym == '*')
      break;
    Figure& fig = figures[numFigures++];
    if(sym == 'r') {
      std::cin >> fig.p1.x >> fig.p2.y >> fig.p2.x >> fig.p1.y;
      fig.type = RECTANGLE;
    }
    else if(sym == 'c') {
      std::cin >> fig.p1.x >> fig.p1.y >> fig.radius;
      fig.type = CIRCLE;
    }
    else {
      std::cin >> fig.p1.x >> fig.p1.y >> fig.p2.x >> fig.p2.y >> fig.p3.x >> fig.p3.y;
      if(!rightTurn(fig.p1,fig.p2,fig.p3))
	 std::swap(fig.p2,fig.p3);
      fig.type = TRIANGLE;
    }
  }
  Point p;
  for(int point = 0; true; ++point) {
    std::cin >> p.x >> p.y;
    if(end(p))
      return 0;
    bool any = false;
    for(int i = 0; i < numFigures; ++i) {
      if(inFigure(p, figures[i])) {
	printf("Point %d is contained in figure %d\n", point+1, i+1);
	any = true;
      }
    }
    if(!any)
      printf("Point %d is not contained in any figure\n", point+1);
  }
}
