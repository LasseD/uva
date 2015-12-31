#include <iostream>
#include <stdint.h>
#include <stdio.h>

typedef uint32_t ul;
typedef uint64_t ull;

int main() {
  ul facts[10001];
  facts[0] = facts[1] = 1;
  for(int i = 2; i < 10001; ++i) {
    ull n = i;
    while(n % 10 == 0) {
      n/=10;
    }

    ull prev = facts[i-1];
    ull cur = prev * n;
    while(cur % 10 == 0) {
      cur/=10;
    }
    facts[i] = (ul)(cur % 4000000);
  }
  
  int N;
  while(std::cin >> N) {
    printf("%5d -> %d\n", N, facts[N]%10);
  }
  return 0;
}
