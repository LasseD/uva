#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

typedef unsigned long long ul;

#define NUMBER_OF_PRIMES 25
int primes[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

//  int multipliers[NUMBER_OF_PRIMES];
void factorizeFaculty(int * const multipliers, int N) {
  for(int i = 0; i < NUMBER_OF_PRIMES; ++i) {
    multipliers[i] = 0;
  }
  if(N == 1)
    return;
  // mult up:
  for(int i = 2; i <= N; ++i) {
    int remainder = i;
    int primeIndex = 0;
    while(remainder > 1) {
      while(remainder % primes[primeIndex] == 0) {
	multipliers[primeIndex]++;
	remainder /= primes[primeIndex];
      }
      ++primeIndex;
    }
  }
} 

ul facDiv(int N, std::vector<int> divs) {
  int multipliers[NUMBER_OF_PRIMES];
  factorizeFaculty(multipliers, N);

  for(unsigned int i = 0; i < divs.size(); ++i){
    int M = divs[i];
    int m2[NUMBER_OF_PRIMES];
    factorizeFaculty(m2, M);

    for(int j = 0; j < NUMBER_OF_PRIMES; ++j) {
      multipliers[j] -= m2[j];
    }
  }

  ul res = 1;
  for(int i = 0; i < NUMBER_OF_PRIMES; ++i) {
    if(multipliers[i] > 0) {
      for(int j = 0; j < multipliers[i]; ++j)
	res *= primes[i];
    }
  }
  return res;
}

ul nChooseM(int N, int M) {
  std::vector<int> divs;
  divs.push_back(M);
  divs.push_back(N-M);
  return facDiv(N, divs);
}

int main() {
  int N, M;
  while(std::cin >> N >> M) {
    if(N == 0 && M == 0)
      return 0;

    printf("%d things taken %d at a time is %llu exactly.\n", N, M, nChooseM(N,M));
  }
}
