#include <iostream>
#include <bitset>

#define PRIME_LEN 15500

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

  int nextPrime(int n) const {
    if(n == 2)
      return 3;
    if((n & 1) == 0)
      --n;
    int ni = n/2;
    while(!primes[ni])  {
      ++ni;    
    }
    return 1+(ni+1)*2;
  }
  
};

int main() {
  PrimeHandler ph;
  ph.init();

  int N;
  while(std::cin >> N) {
    if(N == 0)
      return 0;
    int ret = 0;
    int low = 2;
    int high = 3;
    int sum = 2; // SUM(low,high-1);

    while(low <= N) {
      if(sum == N) {
	//std::cerr << N << " = [" << low << " + ... + " << high << "[" << std::endl;
	++ret;
	sum -= low;
	low = ph.nextPrime(low);
	sum += high; // remember high is excluded form sum.
	high = ph.nextPrime(high);
      }
      else if(sum < N) {
	sum += high; // remember high is excluded form sum.
	high = ph.nextPrime(high);
      }
      else { // sum > N
	sum -= low;
	low = ph.nextPrime(low);
      }
    }
    
    std::cout << ret << std::endl;      
  }
}
