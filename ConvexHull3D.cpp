#include <iostream>
#include <vector>
#include <cstdlib>

struct Point {
  int x, y, z;
};

struct CHP {
  Point p;
  std::vector<CHP*> n; // neighbours
};

void randomPermutation(std::vector<Point> &v) {
  for(unsigned int i = 0; i < i < v.size()-1; ++i) {
    int swapPos = i + (rand() % (v.size()-i));
    std::swap(v[i], v[swapPos]);
  }
}

class CH {
private:
  std::vector<CHP> pts;
public:
  bool inHull(Point p) const {
    if(pts.size() < 4)
      return false;
    // TODO!
  }
  void add(Point p) {
    // todo!
  }

  CH() {};
  CH(std::vector<Point> points) {
    randomPermutation(points);
    for(unsigned int i = 0; i < points.size(); ++i) {
      if(!inHull(points[i])) {
	add(points[i]);
      }
    }
  }
};
