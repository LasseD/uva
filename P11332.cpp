#include <iostream>

int main() {
  while(true) {
    unsigned long n;
    std::cin >> n;
    if(n == 0)
      return 0;
    while(n >= 10) {
      long sum = 0;
      while(n > 0) {
	sum += n%10;
	n/=10;
      }
      n = sum;
    }
    std::cout << n << std::endl;      
  }
}
