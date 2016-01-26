#include <iostream>
#include <bitset>

#define PRIME_LEN 5000000

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
};

void handleN1(const PrimeHandler &ph, int n) {
  int maxPrime = n-1;
  for(int minPrime = 3; maxPrime > minPrime; minPrime = ph.nextPrime(minPrime)) {
    while(maxPrime+minPrime > n && maxPrime > minPrime) {
      maxPrime = ph.prevPrime(maxPrime);
    }
    if(maxPrime+minPrime == n) {
      std::cout << minPrime << " " << maxPrime << std::endl;
      return;
    }
  }
}

void handleN2(const PrimeHandler &ph, int n) {
  for(int minPrime = 3; true; minPrime = ph.nextPrime(minPrime)) {
    int maxPrime = n-minPrime;
    if(ph.isPrime(maxPrime)) {
      std::cout << minPrime << " " << maxPrime << std::endl;
      return;
    }
  }
}

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  int N;
  while(std::cin >> N) {
    if(N < 8) {
      std::cout << "Impossible." << std::endl;
    }
    else if(N == 8) {
      std::cout << "2 2 2 2" << std::endl;
    }
    else if(N == 9) {
      std::cout << "2 3 2 2" << std::endl;
    }
    else if(N % 2 == 1) {
      std::cout << "2 3 ";
      handleN1(ph, N-5);
    }
    else {
      std::cout << "2 2 ";
      handleN1(ph, N-4);
    }
  }
  return 0;
}
