#include <iostream>
#include <algorithm>

int main() {
  unsigned long N, a[4];
  std::cin >> N;
  for(unsigned long cas = 0; cas < N; ++cas) {
    std::cin >> a[0] >> a[1] >> a[2] >> a[3];
    std::sort(a, a+4);
    if(a[0] == 0 || a[3] >= (a[0]+a[1]+a[2]))
      std::cout << "banana" << std::endl;
    else if(a[0] == a[3])
      std::cout << "square" << std::endl;
    else if(a[0] == a[1] && a[2] == a[3])
      std::cout << "rectangle" << std::endl;
    else
      std::cout << "quadrangle" << std::endl;
  }
}
