#include <bitset>
#define PRIME_LEN 1111111

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

  LL nextPrime(LL n) const {
    LL ni = n/2;
    while(!primes[ni])  {
      ++ni;
      if(ni == PRIME_LEN)
	return -1;
    }
    return 1+(ni+1)*2;
  }
};

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  LL n;
  while(true) {
    std::cin >> n;
    if(n < 0)
      return 0;
    while(n % 2 == 0) { 
      cout << "    2" << endl;
      n /= 2;
    }
    long long prime = 3;
    while(prime > 0 && prime*prime <= n) {
      if(n % prime == 0) {
	cout << "    " << prime << endl;
	n /= prime;
      }
      else
	prime = ph.nextPrime(prime);
    }
    if(n > 1) {
      cout << "    " << n << endl;
    }
    cout << endl;
  }
}
