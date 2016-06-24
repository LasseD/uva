#include <iostream>
#include <stdio.h>
#include <bitset>

#define PRIME_LEN 11000

class PrimeHandler {
  std::bitset<PRIME_LEN> primes;

public:
  void init() {
    primes.set();
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
	primes.set(notAPrimeI, false);
      }
    }    
  }

  bool isPrime(long n) const {
    if(n == 2)
      return true;
    if(n < 2 || (n%2==0))
      return false;
    return primes[n/2-1];
  }

  long nextPrime(long n) const {
    long ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }  
};

void die() {
  int *d = NULL;
  d[0] = 555;
}

int main() {
  int primesUntil[10020]; // idx => primes until and including Euler(idx-1)
  PrimeHandler ph;
  ph.init();

  for(int i = 0; i < 40; ++i)
    primesUntil[i] = i+1;  
  int I = 39;

  long a, b;
  while(std::cin >> a >> b) {
    if(a > b)
      std::swap(a,b);
    if(a < 0 || b > 10000)
      die();
    while(I < b) {
      ++I;
      long eu = I*I+I+41;
      bool prime = true;
      long tryPrime = 3;
      while(tryPrime * tryPrime <= eu) {
	if(eu % tryPrime == 0) {
	  prime = false;
	  break;
	}
	tryPrime = ph.nextPrime(tryPrime);
      }
      primesUntil[I] = primesUntil[I-1] + (prime ? 1 : 0);
    }
    int lowPrimes = 0;
    if(a > 0)
      lowPrimes = primesUntil[a-1];

    printf("%.2f\n", 1e-6+(100.0*(primesUntil[b]-lowPrimes))/((double)(b-a+1)));
  }
}
