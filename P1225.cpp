#include <iostream>
#include <stdio.h>

int main() {
  unsigned int a[100100]; // for i: 10*i+digit is cound for digit.
  for(int i = 0; i < 10; ++i)
    a[i] = 0;
  int max = 0;
  int cases, N;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    std::cin >> N;
    while(max <= N) {
      int copy = max;
      for(int i = 0; i < 10; ++i)
	a[10*(max+1)+i] = a[10*max+i];
      while(copy > 0) {
	++a[10*(max+1)+(copy%10)];
	copy/=10;
      }
      ++max;
    }
    for(int i = 0; i < 10; ++i) {
      if(i != 0)
	std::cout << " ";
      std::cout << a[10*(N+1)+i];
    }
    std::cout << std::endl;
  }
  return 0;
}
