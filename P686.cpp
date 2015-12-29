#include <iostream>
#include <vector>

bool isPrime(unsigned int p, const std::vector<unsigned int> &primes) {
  for(std::vector<unsigned int>::const_iterator it = primes.begin(); it != primes.end(); ++it) {
    if(p % *it == 0)
      return false;
  }
  return true;
}

unsigned int upperBound(unsigned int n, const std::vector<unsigned int> &p) {
  unsigned int low = 0;
  unsigned int high = p.size()-1;
  while(low < high-1) {
    unsigned int mid = (low+high)/2;
    if(n < p[mid])
      high = mid;
    else
      low = mid;
  }
  return high;
}

int main() {
  // Compute prime numbers:
  std::vector<unsigned int> primes;
  primes.push_back(3);
  primes.push_back(5);
  for(unsigned int i = 7; i < 32768; i+=2) {
    if(isPrime(i, primes))
      primes.push_back(i);
  }
  
  unsigned int n;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    if(n == 4) {
      std::cout << 1 << std::endl;
      continue;
    }

    unsigned int top = upperBound(n,primes);
    int cnt = 0;
    for(unsigned int bottom = 0; top > bottom; ++bottom) {
      while(primes[top]+primes[bottom] > n && top > bottom)
	--top;
      if(primes[top]+primes[bottom] == n) {
	//std::cerr << n << " = " << primes[top] << "+" << primes[bottom] << std::endl;
	++cnt;
      }
    }
    std::cout << cnt << std::endl;
  }
}
