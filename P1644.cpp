#include <iostream>
#include <bitset>

#define PRIME_LEN 649855

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
  
  int prevPrime(int n) const {
    int ni = n/2-2;
    while(!primes[ni])
      --ni;
    return 1+(ni+1)*2;
  }

  int primeGap(int n) {
    if(isPrime(n)) {
      //std::cerr << n << " is prime." << std::endl;
      return 0;
    }
    if(n%2 == 1)
      ++n;
    int prev = isPrime(n-1) ? n-1 : prevPrime(n-1);
    int next = isPrime(n+1) ? n+1 : nextPrime(n+1);
    //std::cerr << n << ": " << prev << "->" << next << std::endl;
    return next-prev;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  int n;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    std::cout << ph.primeGap(n) << std::endl;
  }
}
