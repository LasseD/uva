#include <iostream>
#include <stdio.h>

int main() {
  int cases, M, C, K, prices[20];
  bool obtainablePrices[201];
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    std::cin >> M >> C;
    for(int i = 1; i <= M; ++i)
      obtainablePrices[i] = false;
    obtainablePrices[0] = true; // 0 product types OK.

    for(int i = 0; i < C; ++i) {
      std::cin >> K;
      for(int j = 0; j < K; ++j)
	std::cin >> prices[j];
      for(int price = M; price >= 0; --price) {
	if(!obtainablePrices[price])
	  continue; // already set to false and can't propagate.
	for(int j = 0; j < K; ++j) {
	  if(prices[j] + price <= M) {
	    obtainablePrices[prices[j]+price] = true;
	    //std::cerr << "Price " << j << "=" << prices[j] << " => " << prices[j]+price << " obtainable." << std::endl;
	  }
	}
	obtainablePrices[price] = false;
      } // for price
    } // for i

    bool written = false;
    for(int i = M; i >= 0; --i) {
      if(obtainablePrices[i]) {
	written = true;
	std::cout << i << std::endl;
	break;
      }
    }
    if(!written)
      std::cout << "no solution" << std::endl;
    
  }
  return 0;
}
