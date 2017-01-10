#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define PRIME_LEN 50000

typedef long long ll;

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

void factorize(ll n, vector<ll> &ret, PrimeHandler &ph) {
  while(n % 2 == 0) {
    ret.push_back(2);
    n /= 2;
  }
  ll prime = 3;
  while(prime*prime <= n) {
    if(n % prime == 0) {
      ret.push_back(prime);
      n /= prime;
    }
    else {
      prime = ph.nextPrime(prime);
    }
  }
  if(n > 1) {
    ret.push_back(n);
  }
}

bool mDividesNFac(ll n, ll m, PrimeHandler &ph) {
  vector<ll> mParts;
  if(m == 0)
    return false; // 0 divides nothing
  if(m == 1)
    return true; // 1 divides everything.
  if(n == 0)
    return m == 1;
  
  factorize(m, mParts, ph);
  ll surplus = 1;
  set<ll> used;
  for(vector<ll>::const_iterator it = mParts.begin(); it != mParts.end(); ++it) {
    ll factor = *it;
    if(surplus % factor == 0) {
      surplus /= factor;
      continue;
    }
    ll mult = 1;
    while(used.find(mult*factor) != used.end() && mult*factor <= n)
      ++mult;
    if(mult*factor > n)
      return false;
    used.insert(mult*factor);
    surplus *= mult;
  }
  return true; // all factors usable.
}

int main() {
  // Compute prime numbers:
  PrimeHandler ph;
  ph.init();

  ll n, m;
  while(cin >> n >> m) {
    if(mDividesNFac(n, m, ph))
      cout << m << " divides " << n << "!" << endl;
    else
      cout << m << " does not divide " << n << "!" << endl;
  }
  return 0;
}
