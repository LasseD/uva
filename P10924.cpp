#include <iostream>
#include <stdio.h>

#define PRIME_LEN 500000

class PrimeHandler {
  bool primes[PRIME_LEN];

public:
  void init() {
    for(int i = 0; i < PRIME_LEN; ++i)
      primes[i] = true;
    // Sieve primes:
    for(int i = 0; i*i < PRIME_LEN; ++i) {
      if(!primes[i])
	continue;
      // Mark all uneven multiples as non-prime:
      int basePrime = 1+2*(i+1);
      for(int multiple = 3; true; multiple += 2) {
	int notAPrime = basePrime*multiple;
	int notAPrimeI = notAPrime/2-1;
	if(notAPrimeI >= PRIME_LEN)
	  break;
	primes[notAPrimeI] = false;
      }
    }
  }
  
  bool isPrime(int n) const {
    if(n == 2 || n == 1) // WARNING: 1 IS NOT A PRIME!
      return true;
    if(n < 2 || (n%2==0))
      return false;
    return primes[n/2-1];
  }
};

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  char w[250];
  while(gets(w)) {
    int sum = 0;
    char c;
    for(int i = 0; isprint(c = w[i]); ++i) {
      if(c >= 'a' && c <= 'z') {
	sum += (c-'a')+1;
      }
      else if(c >= 'A' && c <= 'Z') {
	sum += (c-'A')+27;
      }
    }
    if(ph.isPrime(sum))
      std::cout << "It is a prime word." << std::endl;
    else
      std::cout << "It is not a prime word." << std::endl;      
  }
  return 0;
}
