#define PRIME_LEN 1000000

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
  
  int nextPrime(int n) const {
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }

  bool isBigPrime(int n) const { // When n is big and odd:
    int p = 3;
    while(p * p <= n) {
      if(n % p == 0)
	return false;
      p = nextPrime(p);
    }
    return true;
  }

  bool isPrime(int n) const {
    if(n == 2)
      return true;
    if(n < 2 || (n%2==0))
      return false;

    if(n/2-1 >= PRIME_LEN)
      return isBigPrime(n);    
    return primes[n/2-1];
  }
};

int main() {
  PrimeHandler ph;

  int N;
  while(cin >> N) {
    if(N <= 4) {
      cout << N << " is not the sum of two primes!" << endl;
    }
    else if((N & 1) == 1) { // odd: Find out if N-2 is prime:
      if(ph.isPrime(N-2))
	cout << N << " is the sum of 2 and " << N-2 << "." << endl;
      else
	cout << N << " is not the sum of two primes!" << endl;	
    }
    else {
      // Normal case: N is even.
      int p2 = N/2;
      if((p2 & 1) == 0)
	++p2; // Make p2 odd.
      int p1 = N-p2; // p1 <= p2
      if(p1 == p2) {
	p2 += 2;
	p1 -= 2;
      }
      while(p1 > 1 && !(ph.isPrime(p2) && ph.isPrime(p1))) {
	p2 += 2;
	p1 -= 2;
      }
      if(p1 <= 1)
	cout << N << " is not the sum of two primes!" << endl;	
      else
	cout << N << " is the sum of " << p1 << " and " << p2 << "." << endl;	
    }
  }
  return 0;
}
