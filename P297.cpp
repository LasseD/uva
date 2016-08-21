#include <iostream>
#include <stdio.h>
#include <cstring>

#define SIDE 32
#define SIZE 1024
typedef std::string String;

void paintPixels(bool *pixels, int &si, String &s, int xMin, int xMax, int yMin, int yMax) {
  //std::cerr << "painting for " << s[si] << ", x [" << xMin << ";" << xMax << "], y [" << yMin << ";" << yMax << "[" << std::endl;
  char c = s[si++];
  if(c == 'f') { // f => black. Paint all:
    for(int x = xMin; x < xMax; ++x) {
      for(int y = yMin; y < yMax; ++y) {
	pixels[y*SIDE + x] = true;
      }
    }
  }
  else if(c == 'p') {// Recurse
    paintPixels(pixels, si, s, xMin, (xMin+xMax)/2, yMin, (yMin+yMax)/2);
    paintPixels(pixels, si, s, (xMin+xMax)/2, xMax, yMin, (yMin+yMax)/2);
    paintPixels(pixels, si, s, xMin, (xMin+xMax)/2, (yMin+yMax)/2, yMax);
    paintPixels(pixels, si, s, (xMin+xMax)/2, xMax, (yMin+yMax)/2, yMax);
  }
}

int main() {
  bool pixels[SIZE];
  int n;
  String s;
  std::cin >> n;
  for(int cas = 0; cas < n; ++cas) {
    for(int i = 0; i < SIZE; ++i)
      pixels[i] = false;
    //memset(pixels, false, SIZE);
    int si = 0;
    std::cin >> s;
    paintPixels(pixels, si, s, 0, SIDE, 0, SIDE);
    si = 0;
    std::cin >> s;
    paintPixels(pixels, si, s, 0, SIDE, 0, SIDE);

    int ret = 0;
    for(int i = 0; i < SIZE; ++i) {
      if(pixels[i])
	++ret;
    }
    std::cout << "There are " << ret << " black pixels." << std::endl;
  }
  return 0;
}
