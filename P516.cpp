#include <iostream>
#include <stdio.h>

#define PRIME_LEN 16400

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

bool readInt(char *w, int &pos, int &a) {
  a = 0;
  char c;
  while(isprint(c = w[pos++])) {
    if(c >= '0' && c <= '9')
      a = 10*a+(c-'0');
    else if(a != 0)
      return true;
  }
  return false;
}

int slowExp(int p, int e) {
  int ret = 1;
  for(int i = 0; i < e; ++i)
    ret*=p;
  return ret;
}

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  int p, e;
  char w[1000];
  while(true) {
    // Compute n:
    gets(w);
    int n = 1;
    int pos = 0;
    readInt(w, pos, p);
    if(p == 0)
      return 0;
    while(true) {
      bool go = readInt(w, pos, e);
      n *= slowExp(p, e);
      if(!go)
	break;
      readInt(w, pos, p);
    }

    // Subtract one:
    //std::cerr << "For n=" << n << " outputting n-1 = " << (n-1) << std::endl;
    --n;

    // Output new value:
    int prime = n % 2 == 0 ? n+1 : n;
    prime = ph.nextPrime(prime);
    bool first = true;
    while(prime >= 3) {
      int times = 0;
      while(n % prime == 0) {
	n /= prime;
	++times;
      }
      if(times > 0) {
	if(!first)
	  std::cout << " ";
	first = false;
	std::cout << prime << " " << times;	
      }
      prime = ph.prevPrime(prime);
    }    
    int times2 = 0;
    while(n % 2 == 0) {
      n /= 2;
      ++times2;
    }
    if(times2 > 0) {
      if(!first)
	std::cout << " ";
      std::cout << 2 << " " << times2;
    }
    std::cout << std::endl;
  }
}
