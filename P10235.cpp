#include <iostream>
#include <vector>

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

  bool isPrime(long n) const {
    if(n == 2)
      return true;
    if(n < 2 || (n%2==0))
      return false;
    return primes[n/2-1];
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  long n;
  while(std::cin >> n) {
    long rev = 0;
    long remainder = n;
    while(remainder > 0) {
      rev = 10*rev + (remainder%10);
      remainder /= 10;
    }
    bool isPrime = ph.isPrime(n);
    bool isEmirp = isPrime && n != rev && ph.isPrime(rev);
    if(!isPrime)
      std::cout << n << " is not prime." << std::endl;
    else if(isEmirp)
      std::cout << n << " is emirp." << std::endl;
    else
      std::cout << n << " is prime." << std::endl;
  }
}
