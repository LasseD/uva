#include <iostream>
#include <stdio.h>
#include <vector>

void factorize(unsigned long n, std::vector<unsigned int> &factors) {  
  //std::cerr << "Divisors of " << n << ":";
  while(n % 2 == 0) {
    //std::cerr << " 2";
    factors.push_back(2);
    n >>= 1;
  }
  unsigned int z = 3;
  while(z * z <= n) {
    if(n % z == 0) {
      //std::cerr << " " << z;
      factors.push_back(z);
      n /= z;
    }
    else {
      z+=2;
    }
  }

  if(n > 1) {
    //std::cerr << " " << n;
    factors.push_back(n);
  }
  //std::cerr << std::endl;
}

int main() {  
  long n;
  while(std::cin >> n) {
    if(n == 0)
      return 0;
    std::vector<unsigned int> factors;
    factorize(n, factors);

    // Count divisors using http://mathschallenge.net/library/number/number_of_divisors
    long divisors = 1;
    int count = 1;
    for(unsigned int i = 1; i < factors.size(); ++i) {
      if(factors[i] == factors[i-1])
	++count;
      else {
	divisors *= count+1;
	count = 1;
      }
    }
    if(n > 1)
      divisors *= count+1;
    //std::cerr << "Divisor count: " << divisors << std::endl;
    
    if(divisors % 2 == 0) {
      std::cout << "no" << std::endl;
    }
    else {
      std::cout << "yes" << std::endl;
    }
  }
}
