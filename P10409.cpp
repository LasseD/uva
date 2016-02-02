#include <iostream>

#define TOP 0
#define BOTTOM 1
#define NORTH 2
#define EAST 3
#define SOUTH 4
#define WEST 5

void toggleNorth(int &s) {
  //std::cerr << "Toggling north" << std::endl;
  switch(s) {
  case TOP:
    s = NORTH;
    break;
  case NORTH:
    s = BOTTOM;
    break;
  case BOTTOM:
    s = SOUTH;
    break;
  case SOUTH:
    s = TOP;
    break;
  }
}
void toggleSouth(int &s) {
  //std::cerr << "Toggling south" << std::endl;
  toggleNorth(s);
  toggleNorth(s);
  toggleNorth(s);
}

void toggleWest(int &s) {
  //std::cerr << "Toggling west" << std::endl;
  switch(s) {
  case TOP:
    s = WEST;
    break;
  case WEST:
    s = BOTTOM;
    break;
  case BOTTOM:
    s = EAST;
    break;
  case EAST:
    s = TOP;
    break;
  }
}
void toggleEast(int &s) {
  //std::cerr << "Toggling east" << std::endl;
  toggleWest(s);
  toggleWest(s);
  toggleWest(s);
}

int main() {
  int N;
  std::string s;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    int s1 = TOP;
    int s2 = NORTH;
    int s3 = WEST;
    for(int i = 0; i < N; ++i) {
      //std::cerr << "START s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << std::endl;
      std::cin >> s;
      switch(s[0]) {
      case 'n':
	toggleNorth(s1);
	toggleNorth(s2);
	toggleNorth(s3);
	break;
      case 's':
	toggleSouth(s1);
	toggleSouth(s2);
	toggleSouth(s3);
	break;
      case 'e':
	toggleEast(s1);
	toggleEast(s2);
	toggleEast(s3);
	break;
      default: //case 'w':
	toggleWest(s1);
	toggleWest(s2);
	toggleWest(s3);
	break;
      }
      //std::cerr << "END s1: " << s1 << ", s2: " << s2 << ", s3: " << s3 << std::endl;
    }

         if(s1 == TOP)
      std::cout << 1 << std::endl;
    else if(s1 == BOTTOM)
      std::cout << 6 << std::endl;
    else if(s2 == TOP)
      std::cout << 2 << std::endl;
    else if(s2 == BOTTOM)
      std::cout << 5 << std::endl;
    else if(s3 == TOP)
      std::cout << 3 << std::endl;
    else// if(s3 == BOTTOM)
      std::cout << 4 << std::endl;
  }
}
