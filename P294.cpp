#define PRIME_LEN 16000
#define EVEN(a) (((a) & 1) == 0)
#define ODD(a) (((a) & 1) == 1)

typedef unsigned long ul;

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

  int numberOfDivisors(ul n) {
    int ret = 1;
    // Handle factor 2:
    while(EVEN(n)) {
      n >>= 1;
      ++ret;
    }

    ul prime = 3;
    while(prime*prime <= n) {
      int occurencesOfPrime = 1;
      while(n % prime == 0) {
	++occurencesOfPrime;
	n /= prime;
      }
      ret *= occurencesOfPrime;
      prime = nextPrime(prime);
    }
    if(prime <= n)
      ret*=2; // n is also a factor.
    return ret;
  }

  ul withMostDivisors(ul L, ul U) {
    ul best = L;
    int bestDivisors = numberOfDivisors(L);
    for(ul i = L+1; i<=U; ++i) {
      int divisorsI = numberOfDivisors(i);
      if(divisorsI > bestDivisors) {
	best = i;
	bestDivisors = divisorsI;
      }
    }
    return best;
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  ul N, U, L;
  cin >> N;
  for(ul cas = 0; cas < N; ++cas) {
    cin >> U >> L;
    if(U < L)
      swap(U,L);
    
    ul P = ph.withMostDivisors(L, U);
    cout << "Between " << L << " and " << U << ", " << P << " has a maximum of " << ph.numberOfDivisors(P) << " divisors." << endl;
  }
}
