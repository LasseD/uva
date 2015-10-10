#include <iostream>

int main() {
  int T;
  std::cin >> T;
  for(int ii = 0; ii < T; ++ii) {
    int x0, y0, x1, y1, cx, cy, r;
    std::cin >> x0 >> y0 >> x1 >> y1 >> cx >> cy >> r;
    x1 -= x0;
    cx -= x0;
    y1 -= y0;
    cy -= y0;
    if(x1 * 6 == y1 * 10 && // Total size
       cy * 2 == y1 && cx * 20 == x1 * 9 && // Position of Sun
       r * 6 == y1 * 2) // Radius
      std::cout << "YES" << std::endl;
    else
      std::cout << "NO" << std::endl;
  }
}
