#define PRIME_LEN 10000

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

  int nextPrime(int n) const {
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }
  
  int prevPrime(int n) const {
    int ni = n/2-2;
    while(!primes[ni])
      --ni;
    return 1+(ni+1)*2;
  }

};

int main() {
  PrimeHandler ph;
  ph.init();
  
  int N;
  FORCAS {
    cin >> N;
    int minPX = N*N;
    int minX;
    int x = 2;
    while(x <= N) {
      int p = N/x;
      if(p*x < minPX) {
	minPX = p*x;
	minX = x;
      }
      x = ph.nextPrime(x);
    }
    cout << minX << endl;
  }
}
