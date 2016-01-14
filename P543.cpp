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
    /*
    // Debugging:
    int numPrimes = 1;
    for(int i = 0; i < PRIME_LEN; ++i) {
      if(primes[i])
	++numPrimes;
    }
    std::cerr << numPrimes << " primes found." << std::endl;//*/
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
    //std::cerr << "Returning prev prime(" << n << "): " << (1+(ni+1)*2) << std::endl;
    return 1+(ni+1)*2;
  }
  
  bool isPrime(int n) const {
    if(n == 2)
      return true;
    if(n < 2 || (n%2==0))
      return false;
    return primes[n/2-1];
  }
};

void handleN1(const PrimeHandler &ph, int n) {
  int maxPrime = n-1;
  for(int minPrime = 3; maxPrime > minPrime; minPrime = ph.nextPrime(minPrime)) {
    while(maxPrime+minPrime > n && maxPrime > minPrime) {
      maxPrime = ph.prevPrime(maxPrime);
    }
    if(maxPrime+minPrime == n) {
      std::cout << n << " = " << minPrime << " + " << maxPrime << std::endl;
      return;
    }
  }
}

void handleN2(const PrimeHandler &ph, int n) {
  for(int minPrime = 3; true; minPrime = ph.nextPrime(minPrime)) {
    int maxPrime = n-minPrime;
    if(ph.isPrime(maxPrime)) {
      std::cout << n << " = " << minPrime << " + " << maxPrime << std::endl;
      return;
    }
  }
}

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  int n;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    handleN1(ph, n);
  }
}
