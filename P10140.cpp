#include <iostream>

#define PRIME_LEN 500000

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
  
  bool isPrime(long n) {
    if(n == 2)
      return true;
    if(n < 2 || (n%2==0))
      return false;
    if(n/2-1 < PRIME_LEN)
      return primes[n/2-1];

    // 3+:
    int prime = 3;
    while(sumDigitsFactors <= sumDigitsN && prime*prime <= n) {
      if(n % prime == 0)
	return false;
      prime = nextPrime(prime);
    }
    return true;
  }

  long nextPrime(long n) const {
    long ni = n/2;
    bool ok = true;
    while(!primes[ni])  {
      if(ni >= PRIME_LEN) {
	ok = false;
	break;
      }
      ++ni;      
    }
    if(ok)
      return 1+(ni+1)*2;
    
    //std::cerr << "Returning next prime(" << n << "): " << (1+(ni+1)*2) << std::endl;
    if(n % 2 == 0)
      ++n; // Only check uneven numbers.
    while(!isPrime(n))
      n += 2;
    return n;
  }
};

int main() {
  PrimeHandler ph;
  long L, U;

  while(cin >> L >> U) {
    bool closeDone = false, distDone = false;
    L = ph.nextPrime(L-1);
    long closeL = L, distL = L, closeU = -1, distU = -1;
    long R = L;
    int step = 0;
    while(!(closeDone && distDone)) {
      ++steps;
      long RR = ph.nextPrime(R);
      if(RR > U)
	break;

      if(closeU == -1 || (closeU-closeL)>(RR-R)) {
	closeL = R;
	closeU = RR;
	if(closeU-closeL == 2)
	  closeDone = true;
      }
      if(distU == -1 || (distU-distL)<(RR-R)) {
	distL = R;
	distU = RR;
      }
      R = RR;
    }
    cerr << "Steps: " << steps << endl;
    if(closeU == -1)
      cout << "There are no adjacent primes." << endl;
    else
      cout << closeL << "," << closeU << " are closest, " << distL << "," << distU << " are most distant." << endl;
  }
  return 0;
}
