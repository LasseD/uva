#include <iostream>

int main() {
  unsigned long n, k;
  while(std::cin >> n) {
    std::cin >> k;
    unsigned long s = 0;
    while(n >= k) {
      const unsigned long add = n/k;
      s += add*k;
      n = n - add*k + add;
    }
    s += n;
    std::cout << s << std::endl;      
  }
  return 0;
}
