#include <iostream>

int main() {
  int init, a, b, c;
  while(true) {
    std::cin >> init >> a >> b >> c;
    if(init == 0 && a == 0 && b == 0 && c == 0)
      return 0;
    int sum = 120; // twice clockwise, once counter-clockwise.
    if(a <= init)
      sum += init-a;
    else
      sum += 40-a+init;
    // position is now a.
    if(b >= a)
      sum += b-a;
    else
      sum += 40+b-a;
    // position is now b
    if(c <= b)
      sum += b-c;
    else
      sum += 40+b-c;
    std::cout << (360*sum/40) << std::endl;
  }
}
