#define PRIME_LEN 50000

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

  long long n;
  while(true) {
    cin >> n;
    if(n == 0)
      return 0;
    cout << n << " =";
    bool first = true;
    if(n < 0) {
      cout << " -1";
      first = false;
      n = -n;
    }
    while(n % 2 == 0) {
      if(!first)
	cout << " x";
      first = false;
      cout << " 2";
      n /= 2;
    }
    long long prime = 3;
    while(prime*prime <= n) {
      if(n % prime == 0) {
	if(!first)
	  cout << " x";
	first = false;
	cout << " " << prime;
	n /= prime;
      }
      else {
	prime = ph.nextPrime(prime);
      }
    }
    if(n > 1) {
      if(!first)
	cout << " x";
      cout << " " << n;
    }
    cout << endl;
  }
}
