#include <iostream>
#include <stdio.h>

#define PRIME_LEN 1100

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
    if(n == 2)
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

  char c, w[2009];
  int cases = 0;
  int counts[256];
  gets(w);
  for(int i = 0; isdigit(c = w[i]); ++i)
    cases = 10*cases + (c-'0');

  for(int cas = 1; cas <= cases; ++cas) {
    // Reset data and read:
    gets(w);
    
    for(int i = (int)'0'; i <= (int)'z'; ++i)
      counts[i] = 0;

    for(int i = 0; isprint(c = w[i]); ++i) {
      if(isalnum(c))
	++counts[(int)c];
    }

    std::cout << "Case " << cas << ": ";
    bool any = false;
    for(int i = (int)'0'; i <= (int)'z'; ++i) {
      c = (char)i;
      if(!isalnum(c))
	continue;
      if(ph.isPrime(counts[i])) {
	any = true;
	std::cout << c;
      }
    }
    if(!any)
      std::cout << "empty";
    std::cout << std::endl;
  }
  return 0;
}
