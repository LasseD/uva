#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define X first
#define Y second

typedef std::pair<int,int> Point;
typedef std::vector<Point> pv;
typedef std::vector<pv> pvv;

bool colinear(const Point &a, const Point &b, const Point &c) {
  return ((b.X-a.X)*(c.Y-a.Y) - (b.Y-a.Y)*(c.X-a.X)) == 0;
}

std::ostream& operator<<(std::ostream& os, const Point &p) {
  os << p.X << "," << p.Y;
  return os;
}

int main() {
  while(true) {
    // read points:
    pv points;
    while(true) {
      Point p;
      std::cin >> p.X >> p.Y;
      if(p.X == 0 && p.Y == 0) {
	if(points.empty())
	  return 0;
        break;
      }
      points.push_back(p);
    }
    std::sort(points.begin(), points.end());

    unsigned int psize = points.size();
    unsigned int lsize = points.size()*points.size();
    bool *lookup = new bool[lsize]; // checked lines.
    for(unsigned int i = 0; i < lsize; ++i) {
      lookup[i] = false;
    }

    pvv lines;
    int lineL[10];
    for(unsigned int a = 0; a < points.size()-2; ++a) {
      Point pa = points[a];
      for(unsigned int b = a+1; b < points.size()-1; ++b) {
	if(lookup[psize*a+b])
	  continue;
	lookup[psize*a+b] = true;
	pv line;
	lineL[0] = a;
	lineL[1] = b;
	int lineLI = 2;
	line.push_back(pa);
	Point pb = points[b];
	line.push_back(pb);
	for(unsigned int c = b+1; c < points.size(); ++c) {
	  if(colinear(pa, pb, points[c])) {
	    for(int i = 0; i < lineLI; ++i) {
	      lookup[psize*lineL[i]+c] = true;
	    }
	    line.push_back(points[c]);
	    lineL[lineLI++] = c;
	  }
	}
	if(line.size() > 2) {
	  lines.push_back(line);
	}
      }
    }
    delete[] lookup;

    // output:
    if(lines.empty()) {
      printf("No lines were found\n");
    }
    else {
      printf("The following lines were found:\n");
      for(pvv::const_iterator it = lines.begin(); it != lines.end(); ++it) {
	const pv line = *it;
	for(pv::const_iterator it2 = line.begin(); it2 != line.end(); ++it2) {
	  printf("(%4i,%4i)", it2->X, it2->Y);
	}
	printf("\n");
      }
    }
  }
}
