#include <iostream>

#define PRIME_LEN 50000

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
  
  int nextPrime(int n) const {
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }    
    return 1+(ni+1)*2;
  }
};

long long totient(long long n, PrimeHandler &ph) {
  if(n == 1)
    return 1;
  long long ret = n;

  if(n % 2 == 0)
    ret /= 2;
  while(n % 2 == 0) {
    n /= 2;
  }
  long long prime = 3;
  while(prime*prime <= n) {
    if(n % prime == 0) {
      while(n % prime == 0)
	n /= prime;
      ret *= prime-1;
      ret /= prime;
    }
    else {
      prime = ph.nextPrime(prime);
    }
  }
  if(n > 1) {
    ret *= n-1;
    ret /= n;
  }
  return ret;
}

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  long long n;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    std::cout << totient(n, ph) << std::endl;
  }
}
