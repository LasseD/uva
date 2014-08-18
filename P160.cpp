#include <iostream>
#include <stdio.h>

#define NUMBER_OF_PRIMES 25

// number of primes: 25.
int primes[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

int main() {
  int multipliers[NUMBER_OF_PRIMES];
  
  while(true) {
    int N;
    std::cin >> N;
    if(N == 0)
      return 0;
    for(int i = 0; i < NUMBER_OF_PRIMES; ++i) {
      multipliers[i] = 0;
    }
    // mult up:
    int maxPrimeIndex = 0;
    for(int i = 2; i <= N; ++i) {
      int remainder = i;
      int primeIndex = 0;
      while(remainder > 1) {
	while(remainder % primes[primeIndex] == 0) {
	  multipliers[primeIndex]++;
	  remainder /= primes[primeIndex];
	  maxPrimeIndex = std::max(maxPrimeIndex, primeIndex);
	}
	++primeIndex;
      }
    }
    // output:
    printf("%3i! =", N);
    for(int i = 0; i <= maxPrimeIndex; ++i) {
      if(i > 0 && i % 15 == 0)
	printf("\n      ");
      printf("%3i", multipliers[i]);
    }
    printf("\n");
  }
} 
