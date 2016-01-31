#include <iostream>

int main() {
  int n, m;
  while(true) {
    std::cin >> n >> m;
    if(n == -1 && m == -1)
      return 0;
    if(n > m)
      std::swap(n, m);
    int d1 = m-n;
    int d2 = 100+(n-m);
    if(d1 < d2)
      std::cout << d1 << std::endl;
    else
      std::cout << d2 << std::endl;      
  }
}
