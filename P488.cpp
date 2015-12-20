#include <iostream>

void print(long n) {
  for(int i = 0; i < n; ++i)
    std::cout << n;
  std::cout << std::endl;
}

int main() {
  unsigned long N, A, F;
  std::cin >> N;
  for(unsigned long ignore = 0; ignore < N; ++ignore) {
    std::cin >> A >> F;
    for(unsigned long i = 0; i < F; ++i) {
      if(ignore > 0 || i > 0)
	std::cout << std::endl;
      for(unsigned long j = 1; j < A; ++j)
	print(j);
      for(unsigned long j = A; j > 0; --j)
	print(j);    
    }
  }
  return 0;
}
