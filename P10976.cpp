#include <iostream>
#include <bitset>
#include <set>
#include <vector>

#define PRIME_LEN 10000
#define EVEN(a) (((a) & 1) == 0)
#define ODD(a) (((a) & 1) == 1)

typedef unsigned long ul;
typedef std::set<int> Set;
typedef std::vector<int> Vector;

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

  void addMultiples(ul n, Set &s) {
    Vector toAdd;
    if(s.find(n) == s.end())
      toAdd.push_back(n);
    for(Set::const_iterator it = s.begin(); it != s.end(); ++it) {
      if(s.find(*it*n) == s.end())
	toAdd.push_back(*it*n);
    }
    for(Vector::const_iterator it = toAdd.begin(); it != toAdd.end(); ++it)
      s.insert(*it);
  }

  void findDivisors(ul n, Set &s) {
    // Handle factor 2:
    while(EVEN(n)) {
      n >>= 1;
      addMultiples(2, s);
      addMultiples(2, s); // Because n is squared. Don't do this when borrowing the code!
    }

    ul prime = 3;
    while(prime*prime <= n) {
      while(n % prime == 0) {
	addMultiples(prime, s);
	addMultiples(prime, s); // Because n is squared. Don't do this when borrowing the code!
	n /= prime;
      }
      prime = nextPrime(prime);
    }
    if(prime <= n) {
      addMultiples(n, s); // n is also a factor.
      addMultiples(n, s); // Because n is squared. Don't do this when borrowing the code!
    }
  }
};

int main() {
  PrimeHandler ph;
  ph.init();

  ul k;
  while(std::cin >> k) {
    if(k == 1) {
      std::cout << 1 << std::endl;
      std::cout << "1/1 = 1/2 + 1/2" << std::endl;
      continue;
    }

    Set s;
    ph.findDivisors(k, s);
    
    int sets = 0;
    for(Set::reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
      int x = *it+k;
      int y = x*k/(x-k);
      if(x < y)
	break;
      ++sets;
    }
    std::cout << sets << std::endl;
    for(Set::reverse_iterator it = s.rbegin(); it != s.rend(); ++it) {
      int x = *it+k;
      int y = x*k/(x-k);
      if(x < y)
	break;
      std::cout << "1/" << k << " = 1/" << x << " + 1/" << y << std::endl;
    }
  }
}
