#include <stdio.h>
#include <iostream>
#include <sstream>

typedef std::string String;
typedef std::pair<double,double> PP;
#define X first
#define Y second

double distSq(const PP &a, const PP &b) {
  return (a.X-b.X)*(a.X-b.X)+(a.Y-b.Y)*(a.Y-b.Y);
}

int main() {
  int N;
  PP gopher, dog, hole;
  std::string x, y;
  while(std::cin >> N >> gopher.X >> gopher.Y >> dog.X >> dog.Y) {
    bool escape = false;
    for(int i = 0; i < N; ++i) {
      std::cin >> x >> y; //hole.X >> hole.Y;
      if(escape)
	continue;
      std::stringstream ss1, ss2; ss1 << x; ss2 << y; ss1 >> hole.X; ss2 >> hole.Y;
      if(distSq(dog,hole) >= 4*distSq(gopher,hole)) {
	escape = true;
	std::cout << "The gopher can escape through the hole at (" << x << "," << y << ")." << std::endl;
      }
    }
    if(!escape)
      std::cout << "The gopher cannot escape." << std::endl;
  }
  return 0;
}
