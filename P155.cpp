#include <iostream>
#include <stdio.h>

int get(int k, int kx, int ky, int x, int y) { // side length of square = 2k
  int res = 0;
  // check if in own square:
  if(x >= kx-k && x <= kx+k && y >= ky-k && y <= ky+k) {
    //std::cerr << "(" << x << "," << y << " hits square k=" << k <<", kx="<<kx<<", ky=" << ky << std::endl;
    ++res;
  }
  else {
    //std::cerr << "(" << x << "," << y << " avoids square k=" << k <<", kx="<<kx<<", ky=" << ky << std::endl;
  }
  if(k <= 1 || kx == x || ky == y)
    return res;
  // check square recursively:
  if(x < kx) {
    if(y < ky) {
      res += get(k/2, kx-k, ky-k, x, y);
    }
    else {
      res += get(k/2, kx-k, ky+k, x, y);
    }
  }
  else {
    if(y < ky) {
      res += get(k/2, kx+k, ky-k, x, y);
    }
    else {
      res += get(k/2, kx+k, ky+k, x, y);
    }
  }
  return res;
}

int main() {
  while(true) {
    int k, x, y;
    std::cin >> k >> x >> y;
    if(k == 0 && x == 0 && y == 0)
      return 0;
    int res = get(k, 1024, 1024, x, y);
    printf("%3i\n", res);
  }
}
