#include <iostream>
#include <bitset>

#define PRIME_LEN 500000
#define GAP 115

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
  
  int prevPrime(int n) const {
    if(n <= 2)
      return -1;
    if(n == 3)
      return 2;
    if((n & 1) == 0)
      ++n;
    int ni = n/2-2;
    while(!primes[ni])
      --ni;
    return 1+(ni+1)*2;
  }

  int primeChampion(int L, int U) {
    if(!isPrime(L))
      L = nextPrime(L);
    if(!isPrime(U))
      U = prevPrime(U);
    if(L >= U)
      return -1;
    //std::cerr << "Running " << L << "->" << U << std::endl;

    int a[GAP];
    for(int i = 0; i < GAP; ++i)
      a[i] = 0;
    int largestI = 0;
    while(L < U) {
      int n = nextPrime(L);
      //std::cerr << "Gap: " << (n-L) << std::endl;
      ++a[n-L];
      if(a[n-L] > a[largestI])
	largestI = n-L;
      L = n;
    }
    for(int i = 0; i < GAP; ++i) {
      if(i == largestI)
	continue;
      if(a[i] == a[largestI])
	return -1;
    }
    return largestI;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  int L, U, T;
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> U >> L;
    if(U < L)
      std::swap(U, L);
    int champion = ph.primeChampion(L, U);
    if(champion == -1)
      std::cout << "No jumping champion" << std::endl;
    else
      std::cout << "The jumping champion is " << champion << std::endl;      
  }
}
