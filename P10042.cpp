#include <iostream>

#define PRIME_LEN 40000

int sumDigits(int n) {
  int ret = 0;
  while(n > 0) {
    ret += n%10;
    n/=10;
  }
  return ret;
}

class PrimeHandler {
  bool primes[PRIME_LEN];

public:
  PrimeHandler() {
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
    //std::cerr << "Returning next prime(" << n << "): " << (1+(ni+1)*2) << std::endl;
    
    return 1+(ni+1)*2;
  }

  bool isSmith(int n) {
    if(n < 4)
      return n == 1;
    int sumDigitsN = sumDigits(n);
    bool anyFactors = false;
    int sumDigitsFactors = 0;

    // 2:
    while(n % 2 == 0) {
      sumDigitsFactors += 2;
      n /= 2;
      anyFactors = true;
    }    
    // 3+:
    int prime = 3;
    while(sumDigitsFactors <= sumDigitsN && prime*prime <= n) {
      while(n % prime == 0) {
	sumDigitsFactors += sumDigits(prime);
	n /= prime;
	anyFactors = true;
      }
      prime = nextPrime(prime);
    }
    if(n > 1)
      sumDigitsFactors += sumDigits(n); // last factor.
    return anyFactors && sumDigitsN == sumDigitsFactors;
  }
};

int main() {
  PrimeHandler ph;
  int cases;
  std::cin >> cases;

  long n;
  for(int cas = 0; cas < cases; ++cas) {
    std::cin >> n;
    for(int i = n+1; true; ++i) {
      if(ph.isSmith(i)) {
	std::cout << i << std::endl;
	break;
      }
    }
  }
  return 0;
}
