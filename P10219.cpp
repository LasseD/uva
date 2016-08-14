#include <cmath>
#include <iostream>

int main() {
  unsigned long n, k;
  while(std::cin >> n >> k) {
    // compute log10(n choose k) = log10(n! / (n-k)! / k!)
    long double ret = 1+1e-6;
    for(unsigned int i = 1; i <= k; ++i)
      ret += log10(n-i+1) - log10(i);
    std::cout << (int)ret << std::endl;    
  }
  return 0;
}
