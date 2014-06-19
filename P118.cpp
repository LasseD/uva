#include <iostream>
#include <stdio.h>
#include <set>

typedef std::pair<int,int> xy;

void walk(int &x, int &y, const char dir) {
  switch(dir) {
  case 'E':
    ++x;
    return;
  case 'W':
    --x;
    return;
  case 'N':
    ++y;
    return;
  case 'S':
    --y;
    return;
  }
}

char right(const char dir) {
  switch(dir) {
  case 'E':
    return 'S';
  case 'W':
    return 'N';
  case 'N':
    return 'E';
  case 'S':
    return 'W';
  }
}

char left(const char dir) {
  switch(dir) {
  case 'E':
    return 'N';
  case 'W':
    return 'S';
  case 'N':
    return 'W';
  case 'S':
    return 'E';
  }
}

int main() {
  // Read input:
  int width, height;
  std::cin >> width >> height;
  std::set<xy> lost;
  while(true) {
    int x, y;
    char dir;
    if(!(std::cin >> x >> y >> dir))
      return 0;

    char instructions[101];
    std::cin >> instructions;
    int i = 0;
    int status = 0; // 0 ok, 1 done, 2 fallen.
    while(status == 0) {
      //      std::cerr << "at " << x << " " << y << " " << dir << std::endl;
      char instruction = instructions[i++];
      switch(instruction) {
      case 'R':
	dir = right(dir);
	break;
      case 'L':
	dir = left(dir);
	break;
      case 'F':
	walk(x, y, dir);
	// Check boundary:
	if(x < 0 || y < 0 || x > width || y > height) {
	  //std::cerr << "danger " << x << " " << y << " " << dir << std::endl;
	  // lost:
	  // go back:
	  dir = right(right(dir));
	  walk(x,y,dir);
	  dir = right(right(dir));

	  xy pos(x,y);
	  std::set<xy>::const_iterator it = lost.find(pos);
	  if(it == lost.end()) {
	    std::cout << x << " " << y << " " << dir << " LOST" << std::endl;
	    lost.insert(pos);
	    status = 2;
	  }
	}
	break;
      default:
	//std::cerr << "breaking '" << instruction << "'" << std::endl;
	status = 1;
	break;
      }
    }
    // Output:
    if(status == 1) {
      std::cout << x << " " << y << " " << dir << std::endl;
    }
  }
}
