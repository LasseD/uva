#include <bitset>

#define MIL 1000000
#define PRIME_LEN 500005

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
    if(n == 2)
      return 3;
    int ni = n/2;
    if(ni >= PRIME_LEN)
      cerr << "GEH" << endl;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  int *ret = new int[MIL+1];
  memset(ret, 0, (MIL+1)*sizeof(int));

  for(int i = 2; i <= MIL; ++i) {
    if(ph.isPrime(i)) {
      ret[i] = 1;
      continue;
    }
    // Find first divisor:
    int prime = 2;
    while(i % prime != 0)
      prime = ph.nextPrime(prime);
    ret[i] = 1 + ret[i/prime];
  }

  for(int i = 2; i <= MIL; ++i) {
    ret[i] += ret[i-1];
  }

  int x;
  while(cin >> x) {
    cout << ret[x] << endl;
  }
  return 0;
}
