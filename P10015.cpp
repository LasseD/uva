#define PRIME_LEN 1000000

class PrimeHandler {
  bitset<PRIME_LEN> primes;

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

  long nextPrime(long n) const {
    if(n == 2)
      return 3;
    long ni = n/2;
    while(!primes[ni])  {
      ++ni;
    }
    return 1+(ni+1)*2;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  int ret[3502], pos[3502];
  FORI(3502)
    ret[i] = -1;

  while(true) {
    GI(n);
    if(n == 0)
      return 0;
    FORI(n)
      pos[i] = i+1;
    if(ret[n] == -1) {
      int cur = 0; // Current idx;
      int prime = 2;
      for(int size = n; size > 1; --size) {
	// Kill and move:
	cur += prime-1;
	cur %= size;
	for(int p = cur; p+1 < size; ++p)
	  pos[p] = pos[p+1];
	prime = ph.nextPrime(prime);
      }
      ret[n] = pos[0];
    }    
    cout << ret[n] << endl;
  }
}
