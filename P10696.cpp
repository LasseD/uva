#include <iostream>

unsigned long f91(unsigned long N) {
  if(N <= 100)
    return f91(f91(N+11));
  return N-10;
}

int main() {
  unsigned long N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    std::cout << "f91(" << N << ") = " << f91(N) << std::endl;
  }
}
