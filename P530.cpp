#include <iostream>

typedef unsigned long long ul;

/*
n|k = n!/(k!(n-k)!)
Assume k < n-k (as n|k = n|n-k)
n|k = PRODUCT_i=1..k((n-k+i)/i) - because i=k must divide final product.
 */
ul nChooseK(ul n, ul k) {
  if(n-k < k)
    k = n-k;
  
  ul ret = 1;
  for(ul i = 1; i <= k; ++i)
    ret = (ret * (n-k+i)) / i;
  return ret;
}

int main() {
  ul n, k;
  while(true) {
    std::cin >> n >> k;
    if(n == 0 && k == 0)
      return 0;
    std::cout << nChooseK(n,k) << std::endl;
  }
}
