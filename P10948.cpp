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
    if(n < 2)
      return 2;
    if(n == 2)
      return 3;
    if((n & 1) == 0)
      --n;
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

  int N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    int a = 2;
    while(!ph.isPrime(N-a) && 2*a <= N) {
      a = ph.nextPrime(a);
    }
    if(2*a > N)
      std::cout << N << ":" << std::endl << "NO WAY!" << std::endl;
    else
      std::cout << N << ":" << std::endl << a << "+" << (N-a) << std::endl;
  }
}
