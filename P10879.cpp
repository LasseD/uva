#include <iostream>
#include <bitset>

#define PRIME_LEN 10000

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

  int nextPrime(int n) const {
    if(n == 2)
      return 3;
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  int cases, k;
  std::cin >> cases;
  for(int cas = 1; cas <= cases; ++cas) {
    std::cin >> k;
    int a = 2;
    while(k % a != 0)
      a = ph.nextPrime(a);    
    k/=a;
    int b = a;
    while(k % b != 0)
      b = ph.nextPrime(b);
    std::cout << "Case #" << cas << ": " << k*a << " = " << a << " * " << k << " = " << a*b << " * " << (k/b) << std::endl;
  }
}
