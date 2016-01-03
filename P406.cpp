#include <iostream>
#include <vector>

#define PRIME_LEN 1024

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
    /*
    // Debugging:
    int numPrimes = 1;
    for(int i = 0; i < PRIME_LEN; ++i) {
      if(primes[i])
	++numPrimes;
    }
    std::cerr << numPrimes << " primes found." << std::endl;//*/
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
    //std::cerr << "Returning prev prime(" << n << "): " << (1+(ni+1)*2) << std::endl;
    return 1+(ni+1)*2;
  }
  
  bool isPrime(int n) const {
    if(n == 2)
      return true;
    if(n < 2 || (n%2==0))
      return false;
    return primes[n/2-1];
  }

  void getPrimesUpTo(int n, std::vector<int> &out) {
    out.push_back(1);
    if(n == 1)
      return;
    out.push_back(2);
    for(int prime = 3; prime <= n; prime = nextPrime(prime)) {
      out.push_back(prime);      
    }
  }
};

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  int N, C;
  while(std::cin >> N >> C) {
    std::vector<int> v;
    ph.getPrimesUpTo(N, v);
    std::cout << N << " " << C << ":";
    int numberOfPrimesToPrint = 2*C;
    if(v.size() % 2 == 1)
      --numberOfPrimesToPrint;
    int firstToPrint = ((int)v.size()/2)-numberOfPrimesToPrint/2;
    if(firstToPrint < 0)
      firstToPrint = 0;
    int lastToPrint = firstToPrint+numberOfPrimesToPrint-1;
    if(lastToPrint >= (int)v.size())
      lastToPrint = (int)v.size()-1;
    for(int i = firstToPrint; i <= lastToPrint; ++i)
      std::cout << " " << v[i];
    std::cout << std::endl << std::endl;
  }
}
