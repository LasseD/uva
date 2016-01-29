#include <stdio.h>
#include <iostream>

int readInt(char *w) {
  char c;
  int ret = 0;
  for(int i = 0; isdigit(c = w[i]); ++i)
    ret = 10*ret + (c-'0');
  return ret;
}

int main() {
  char c, w[10009];
  unsigned long prices[256];
  gets(w);
  int N = readInt(w);
  for(int cas = 0; cas < N; ++cas) {
    // Read prices:
    for(int i = 0; i < 256; ++i)
      prices[i] = 0;
    gets(w);
    int K = readInt(w);
    for(int i = 0; i < K; ++i) {
      gets(w);
      prices[128+w[0]] = readInt(&w[2]);
      std::cerr << "Price of " << ((int)w[0]) << std::endl;
    }

    // Compute:
    gets(w);
    int M = readInt(w);
    unsigned long cost = 0;
    for(int i = 0; i < M; ++i) {
      gets(w);
      for(int j = 0; '\0' != (c = w[j]); ++j)
	cost += prices[128+c];
    }
    printf("%lu.%.2lu$\n", cost/100, cost%100);
  }
  return 0;
}
