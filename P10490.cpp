// Perfect numbers from https://oeis.org/A000396
long perfect[8] = {6, 28, 496, 8128, 33550336, 8589869056, 137438691328L, 2305843008139952128L};

#define PRIME_LEN 50

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
};

int main() {
  PrimeHandler ph;
  ph.init();

  set<long> allPerfect;
  FORI(8)
    allPerfect.insert(perfect[i]);
  
  int k;
  while(cin >> k) {
    if(k < 1)
      return 0;
    if(!ph.isPrime(k)) {
      cout << "Given number is NOT prime! NO perfect number is available." << endl;
      continue;
    }
    
    long part1 = 1 << (k-1);
    long part2 = (1 << k)-1;
    long n = part1*part2;
    if(allPerfect.find(n) != allPerfect.end())
      cout << "Perfect: " << n << "!" << endl;
    else
      cout << "Given number is prime. But, NO perfect number is available." << endl;
  }
  return 0;
}
