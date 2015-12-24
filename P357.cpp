#include <iostream>
#include <stdio.h>

typedef unsigned long long ll;

#define CURRENCY_TYPES 5
int values[CURRENCY_TYPES] = {1, 5, 10, 25, 50};

int main() {
  ll a[60002];
  int ai = 0;
  int aiPrev = 30001;

  for(int i = 0; i < 30001; ++i) {
    a[i] = 1; // for 1c
  }

  for(int type = 1; type < CURRENCY_TYPES; ++type) {
    std::swap(ai, aiPrev);
    // compute currency type from ai using aiPrev:
    int windowTop = values[type]; // window length
    for(int window = 0; window < windowTop; ++window) {
      ll sum = 0;
      for(int y = window; y < 30001; y+=windowTop) {
	sum += a[aiPrev+y];
	a[ai+y] = sum;
      }
    }
  }
  
  int amount;
  while(std::cin >> amount) {
    ll combinations = a[ai+amount];
    if(combinations == 1)
      printf("There is only 1 way to produce %d cents change.\n", amount);
    else
      printf("There are %llu ways to produce %d cents change.\n", combinations, amount);
  }
}
