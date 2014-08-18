#include <iostream>
#include <stdio.h>

typedef unsigned long long ll;

#define CURRENCY_TYPES 11
int values[CURRENCY_TYPES] = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

int main() {
  ll a[12002];
  int ai = 0;
  int aiPrev = 6001;

  for(int i = 0; i < 6001; ++i) {
    a[i] = 1; // for 5c
  }

  for(int type = 1; type < CURRENCY_TYPES; ++type) {
    std::swap(ai, aiPrev);
    // compute currency type from ai using aiPrev:
    int windowTop = values[type]/5; // window length
    for(int window = 0; window < windowTop; ++window) {
      ll sum = 0;
      for(int y = window; y < 6001; y+=windowTop) {
	sum += a[aiPrev+y];
	a[ai+y] = sum;
      }
    }
  }
  
  /*for(int y = 150; y < 250; ++y)
    std::cerr << "Combinations for " << (y*5) << "c: " << a[aiPrev+y] << std::endl; //*/

  std::string line;
  while(true) {
    std::cin >> line;
    if(line == "0.00")
      return 0;
    int amount = 0;
    for(unsigned int i = 0; i < line.size(); ++i) {
      if(line[i] == '.')
	continue;
      amount = 10*amount + (line[i]-'0');
    }
    ll combinations = a[ai+amount/5];
    printf("%3i.%02i%17llu\n", amount/100, amount%100, combinations);
  }
}
