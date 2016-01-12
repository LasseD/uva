#include <iostream>
#include <bitset>

#define PRIME_LEN 10000000

class PrimeHandler {
  std::bitset<10000000> primes;

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

  void setTwins(unsigned int *twins) {
    int twinI = 0;
    for(int i = 0; i < PRIME_LEN-1; ++i) {
      if(primes[i] && primes[i+1])
	twins[twinI++] = 2*i+3;
    }
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  unsigned int twins[100000];
  ph.setTwins(twins);

  long n;
  while(std::cin >> n) {
    std::cout << "(" << twins[n-1] << ", " << (twins[n-1]+2) << ")" << std::endl;
  }
  return 0;
}
