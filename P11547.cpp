#include <iostream>

int main() {
  int N;
  std::cin >> N;
  for(int ignore = 0; ignore < N; ++ignore) {
    long long n;
    std::cin >> n;
    // Multiply n by 567, then divide the result by 9, then add 7492, then multiply by 235, then divide by 47, then subtract 498. What is the digit in the tens column?
    n*=63;
    n+=7492;
    n*=5;
    n-=498;
    //std::cerr << n << std::endl;
    n/=10;
    n%=10;
    if(n < 0)
      n = -n;
    std::cout << n << std::endl;
  }
  return 0;
}
