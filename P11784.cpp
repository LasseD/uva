#include <iostream>
#include <stdio.h>

typedef std::pair<int,int> PP;
#define X first
#define Y second

void die() {
  int *a = NULL;
  a[6] = 7;
}

PP get(PP size, PP mib, int door) {
  //std::cerr << "GET " << size.X << "x" << size.Y << ", MIB(" << mib.X << "," << mib.Y << "), door=" << door << std::endl;
  // Try up:
  if(mib.Y <= mib.X-door) {
    //std::cerr << " UP " << std::endl;
    return PP(mib.X-door, mib.Y);
  }

  // Try right:
  int buffer = size.X-1-door; // How much additional time he has.
  if(size.X-1-mib.X <= buffer + mib.Y) {
    //std::cerr << " RIGHT " << std::endl;
    return PP(buffer + mib.Y, size.X-1-mib.X);
  }

  // Must go below:
  buffer += size.Y-1;
  return PP(buffer+size.X-1-mib.X,size.Y-1-mib.Y);
}

int main() {
  int H;
  PP mib, doors[4000], size;
  while(true) {
    std::cin >> size.Y >> size.X >> H;
    if(size.X == 0 && size.Y == 0 && H == 0)
      return 0;
    for(int i = 0; i < H; ++i) {
      std::cin >> doors[i].Y >> doors[i].X;
      if(doors[i].X >= size.X || doors[i].Y >= size.Y)
	die();
    }
    std::cin >> mib.Y >> mib.X;
    if(mib.X >= size.X-1 || mib.Y >= size.Y-1)
      die();
    PP best(9999,9999);
    for(int i = 0; i < H; ++i) {
      PP SIZE = size, MIB = mib, d = doors[i];
      int door;

      if(d.Y == 0 && d.X < SIZE.X-1) { // Top door
	//std::cerr << "TOP" << std::endl;
	door = d.X;
	// all OK!
      }
      else if(d.X == SIZE.X-1 && d.Y < SIZE.Y-1 ) {
	//std::cerr << "RIGHT" << std::endl;
	std::swap(SIZE.X, SIZE.Y);
	MIB = PP(mib.Y, size.X-1-mib.X);
	door = d.Y;
      }
      else if(d.Y == SIZE.Y-1 && d.X > 0) { // bottom!
	//std::cerr << "BOTTOM" << std::endl;
	MIB = PP(size.X-1-mib.X, size.Y-1-mib.Y);
	door = size.X-1-d.X;
      } 
      else { // left
	//std::cerr << "LEFT" << std::endl;
	std::swap(SIZE.X, SIZE.Y);
	MIB = PP(size.Y-1-mib.Y, mib.X);
	door = size.Y-1-d.Y;
      }
      PP attempt = get(SIZE, MIB, door);
      //std::cerr << "=> " << attempt.X << ", " << attempt.Y << std::endl;
      if(attempt < best)
	best = attempt;
    }
    std::cout << (1+best.first) << " " << (1+best.second) << std::endl;
  }
}
