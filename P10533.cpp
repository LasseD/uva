#include <iostream>
#include <bitset>

#define PRIME_MAX 1000002
#define PRIME_LEN  500001

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
  bool isDigitPrime(long n) const {
    if(!isPrime(n)) {
      return false;
    }
    int p2 = 0;
    while(n > 0) {
      p2 += n%10;
      n/=10;
    }
    return isPrime(p2);
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  int *counts = new int[PRIME_MAX];
  counts[0] = counts[1] = 0;
  int countsTo = 1;

  int N, t1, t2;
  std::cin >> N;
  for(int cas = 0; cas < N; ++cas) {
    std::cin >> t1 >> t2;
    if(t2 < t2)
      std::swap(t1, t2);
    while(countsTo < t2) {
      ++countsTo;
      counts[countsTo] = counts[countsTo-1] + (ph.isDigitPrime(countsTo) ? 1 : 0);
    }

    //std::cerr << t1 << " -> " << t2 << std::endl;
    std::cout << (counts[t2]-counts[t1-1]) << std::endl;
  }
}
