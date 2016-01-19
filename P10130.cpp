#include <iostream>
#include <stdio.h>
#include <algorithm>

typedef std::pair<int,int> Item;

#define W first
#define P second

int main() {
  Item items[1000];
  long maxValue[31];
  
  int T, N, G, MW; // num cases, num items, num people, max weight.
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> N;
    for(int i = 0; i < N; ++i) {
      std::cin >> items[i].P;
      std::cin >> items[i].W;
    }

    // Compute best prices:
    std::sort(items, items+N);
    for(int w = 0; w < 31; ++w) {
      maxValue[w] = 0;
    }
    for(int itemI = 0; itemI < N; ++itemI) {
      Item &item = items[itemI];
      for(int w = 30; w >= item.W; --w) { // Notice: decrementing here causes max 1 of each type of item.
	long newW = item.P + maxValue[w-item.W];
	if(newW > maxValue[w])
	  maxValue[w] = newW;
      }
    }
    /*for(int w = 0; w < 31; ++w) {
      std::cerr << w << ": " << maxValue[w] << ", " << std::endl;
    }//*/

    // Use data:
    std::cin >> G;
    long sum = 0;
    for(int i = 0; i < G; ++i) {
      std::cin >> MW;
      sum += maxValue[MW];
    }
    std::cout << sum << std::endl;
  }
  return 0;
}
