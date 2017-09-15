#define PRIME_LEN 2000000

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
  }
  
  int nextPrime(int n) const {
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }    
    return 1+(ni+1)*2;
  }
};

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  LL n;
  while(true) {
    cin >> n;
    if(n == 0)
      return 0;
    //cerr << n << "->";

    int factors = 0;

    if(n < 0) {
      n = -n;
    }
    LL L = -1; // Largest factor
    if(n % 2 == 0) {
      ++factors;
      L = 2;
      while(n % 2 == 0)
	n /= 2;
    }
    LL prime = 3;
    while(prime*prime <= n) {
      if(n % prime == 0) {
	++factors;
	L = prime;
	while(n % prime == 0)
	  n /= prime;
      }
      prime = ph.nextPrime(prime);
    }
    if(n > 1) {
      ++factors;
      L = n;
    }
    if(L == -1 || factors <= 1)
      cout << -1 << endl;
    else
      cout << L << endl;
  }
}
