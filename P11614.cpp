#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cmath>

typedef unsigned long long ul;

ul sizeTriangle(ul rows) {
  return rows*(rows+1)/2;
}

int main() {
  ul N, T;
  std::cin >> T;
  for(ul cas = 0; cas < T; ++cas) {
    std::cin >> N;
    ul lower = (int)(sqrt(N)-0.5);
    ul upper = lower;
    while(sizeTriangle(upper) <= N)
      upper = upper*10+1;

    std::cerr << "Init lower=" << lower << " for N=" << N << std::endl;
    while(lower < upper-1) {
      ul mid = (lower+upper)/2;
      if(sizeTriangle(mid) <= N)
	lower = mid;
      else
	upper = mid;
    }
    std::cout << lower << std::endl;
  }
  return 0;
}
