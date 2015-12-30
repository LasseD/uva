#include <iostream>
#include <cmath>

int main() {
  int a, b;
  while(true) {
    std::cin >> a >> b;
    if(a == 0 && b == 0)
      return 0;
    int root = (int)sqrt(a);
    if(root*root < a)
      ++root;
    int ret = 0;
    while(root*root <= b) {
      ++root;
      ++ret;
    }
    std::cout << ret << std::endl;
  }
}
