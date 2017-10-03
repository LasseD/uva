#define PRIME_LEN 1000000

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

  long low, high;

  FORCAS {
    cin >> low >> high;
    long ret = 0;
    long basePrime = 2;
    while(basePrime*basePrime <= high) {
      long almostPrime = basePrime*basePrime;
      while(almostPrime <= high) {
	if(almostPrime >= low)
	  ++ret;
	
	almostPrime*=basePrime;
      }
      
      basePrime = ph.nextPrime(basePrime);
    }
    cout << ret << endl;
  }
  return 0;
}
