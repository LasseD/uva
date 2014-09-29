#include <iostream>
#include <stdio.h>
#include <cstdlib>

typedef unsigned long long ll;

#define CURRENCY_TYPES 5
int values[CURRENCY_TYPES] = {1, 5, 10, 25, 50};
#define MAX_VAL 7490

int main() {
  ll a[2*MAX_VAL];
  int ai = 0;
  int aiPrev = MAX_VAL;

  for(int i = 0; i < MAX_VAL; ++i) {
    a[i] = 1; // for 1c
  }

  for(int type = 1; type < CURRENCY_TYPES; ++type) {
    std::swap(ai, aiPrev);
    // compute currency type from ai using aiPrev:
    int windowTop = values[type]/values[0]; // window length
    for(int window = 0; window < windowTop; ++window) {
      ll sum = 0;
      for(int y = window; y < MAX_VAL; y+=windowTop) {
	sum += a[aiPrev+y];
	a[ai+y] = sum;
      }
    }
  }
  
  /*for(int y = 150; y < 250; ++y)
    std::cerr << "Combinations for " << (y*5) << "c: " << a[aiPrev+y] << std::endl; //*/

  std::string line;
  while(getline(std::cin, line)) {
    int amount = atoi(line.c_str());
    ll combinations = a[ai+amount/values[0]];
    std::cout << combinations << std::endl;
  }
}
