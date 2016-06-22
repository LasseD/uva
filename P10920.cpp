#include <iostream>
#include <cmath>

typedef long ul;

int main() {
  ul SZ, P;
  while(true) {
    std::cin >> SZ >> P; // 1,...
    if(SZ == 0 && P == 0)
      return 0;
    ul sideLength = SZ;//(ul)sqrt(SZ+0.5); (SZ is not the full size!

    // Ring sizes: 1, 9, 25 = uneven squares
    ul ringWidth = (ul)sqrt(P-0.5);
    if(ringWidth > 0 && ringWidth % 2 == 0)
      --ringWidth;
    ul rest = P-1 - ringWidth*ringWidth; 

    ul mid = sideLength/2;
    ul right = mid + ringWidth/2 + 1;
    ul left = mid - ringWidth/2 - 1;

    //std::cerr << "P=" << P << ", side length=" << sideLength << ", ring width=" << ringWidth << ", mid=" << mid << ", rest=" << rest << ", right=" << right << ", left=" << left << std::endl;

    ul x, y;
    if(P == 1) {
      //std::cerr << "MID" << std::endl;
      x = y = mid;
    }
    else if(rest < ringWidth+1) {
      //std::cerr << "TOP" << std::endl;
      // Top row:
      x = right-1 - rest;
      y = right;
    }
    else if(rest < 2*(ringWidth+1)) {
      //std::cerr << "LEFT" << std::endl;
      // Left row:
      x = left;
      y = right-1-(rest-(ringWidth+1));
    }
    else if(rest < 3*(ringWidth+1)) {
      //std::cerr << "BOTTOM" << std::endl;
      // Bottom row:
      x = left+1 + (rest-2*(ringWidth+1));
      y = left;
    }
    else {
      //std::cerr << "RIGHT" << std::endl;
      // Right row:
      x = right;
      y = left+1 + (rest-3*(ringWidth+1));
    }
    ++x;
    ++y;
    std::cout << "Line = " << y << ", column = " << x << "." << std::endl;
  }
}
