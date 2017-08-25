#include <bitset>

#define PRIME_LEN 50000
#define PRIME_LEN_HIGH 1000002

class PrimeHandler {
  std::bitset<PRIME_LEN> primes;
  std::bitset<PRIME_LEN_HIGH> highPrimes;

public:
  void init() {
    primes.set();
    // Sieve primes:
    for(long i = 0; i*i < PRIME_LEN; ++i) {
      if(!primes[i])
	continue;
      // Mark all uneven multiples as non-prime:
      long basePrime = 1+2*(i+1);
      for(long multiple = 3; true; multiple += 2) {
	long notAPrime = basePrime*multiple;
	long notAPrimeI = notAPrime/2-1;
	if(notAPrimeI >= PRIME_LEN)
	  break;
	primes.set(notAPrimeI, false);
      }
    }
  }

  long nextPrimeLow(long n) const {
    if(n == 2)
      return 3; // Special case.
    long ni = n/2;
    if(ni >= PRIME_LEN)
      dieSlowly();

    while(!primes[ni])  {
      ++ni;      
    }
    return 1+(ni+1)*2;
  }
  
  void go(long L, long U) {
    if(L < 0 || U < 0 || L > U || U > 2147483647 || U-L > PRIME_LEN_HIGH)
      dieSlowly();

    //cerr << "L=" << L << ", U=" << U << endl;
    highPrimes.set();
    // Sieve primes:
    long prime = 2;
    while(prime*prime <= U) {
      long mult = (L+prime-1)/prime;
      if(mult < 2)
	mult = 2;
      for(; mult*prime <= U; ++mult) {
	highPrimes.set(mult*prime-L, false);
      }
      prime = nextPrimeLow(prime);
    }

    long closeL = L, distL = L, closeU = -1, distU = -1;
    // Compute longervals:
    long R = -1;
    for(long RR = L; RR <= U; ++RR) {
      if(!highPrimes[RR-L])
	continue; // not a prime

      if(R != -1 && (closeU == -1 || (closeU-closeL)>(RR-R))) {
	closeL = R;
	closeU = RR;
      }
      if(R != -1 && (distU == -1 || (distU-distL)<(RR-R))) {
	distL = R;
	distU = RR;
      }
      R = RR;
    }

    if(closeU == -1)
      cout << "There are no adjacent primes." << endl;
    else
      cout << closeL << "," << closeU << " are closest, " << distL << "," << distU << " are most distant." << endl;

  }
};

int main() {
  PrimeHandler ph;
  ph.init();
  long L, U;

  while(cin >> L >> U) {
    if(L < 2)
      L = 2;
    if(U < L)
      U = L;
    ph.go(L, U);
  }
  return 0;
}
