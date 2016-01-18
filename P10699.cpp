#include <iostream>
#include <bitset>

#define PRIME_LEN 500000

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

  int nextPrime(int n) const {
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }

  int countFactors(int n) const {
    int ret = 0;
    while((n & 1) == 0) {
      n >>= 1;
      ret = 1;
    }
    for(int prime = 3; prime <= n; prime = nextPrime(prime)) {
      if(n % prime != 0)
	continue;
      ++ret;
      do {
	n /= prime;
      } while(n % prime == 0);
    }
    return ret;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  int N;
  while(std::cin >> N) {
    if(N == 0)
      return 0;
    std::cout << N << " : " << ph.countFactors(N) << std::endl;
  }
}
