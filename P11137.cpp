#include <iostream>
#include <stdio.h>

typedef unsigned long long ll;

#define CURRENCY_TYPES 21

int main() {
  int values[CURRENCY_TYPES];
  for(int i = 1; i <= 21; ++i)
    values[i-1] = i*i*i;

  ll a[20002]; // Twice the size to support dynamic value computation based on prev.
  int ai = 0;
  int aiPrev = 10001;

  for(int i = 0; i < 10001; ++i) {
    a[i] = 1; // for 1c
  }

  for(int type = 1; type < CURRENCY_TYPES; ++type) {
    std::swap(ai, aiPrev);
    // compute currency type from ai using aiPrev:
    int windowTop = values[type]; // window length
    for(int window = 0; window < windowTop; ++window) {
      ll sum = 0;
      for(int y = window; y < 10001; y+=windowTop) {
	sum += a[aiPrev+y];
	a[ai+y] = sum;
      }
    }
  }
  
  int amount;
  while(std::cin >> amount)
    std::cout << a[ai+amount] << std::endl;
}
