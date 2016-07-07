#include <iostream>
#include <stdio.h>
#include <cstring>

#define LEN 510000

bool readInts(long &a, long &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  char w[40];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      if(aDone)
	b = b*10 + (w[i]-'0');
      else {
	a = a*10 + (w[i]-'0');
	aStarted = true;
      }
    }
    else {
      if(!isprint(w[i]))
	break;
      if(aStarted)
	aDone = true;
    }
  }
  return !(a == 0 && b == 0);
}

unsigned int eval(long n, unsigned int *a) {
  if(n < LEN && a[n] != 0)
    return a[n];
  long m = n;
  unsigned int steps = 0;
  while(m != 1 && (m >= LEN || a[m] == 0)) {
    if((m & 1) == 1)
      m = 3*m+1;
    else
      m >>= 1;
    ++steps;
  }
  if(m < LEN && m != 1 && a[m] != 0)
    steps += a[m];
  if(n >= LEN) {
    return steps;
  }
  m = n;
  while(m != 1 && (m >= LEN || a[m] == 0)) {
    if(m < LEN)
      a[m] = steps;
    if((m & 1) == 1)
      m = 3*m+1;
    else
      m >>= 1;
    --steps;
  }
  return a[n];
}

int main() {
  unsigned int a[LEN];
  memset(a, 0, sizeof(a));
  a[1] = 3;
  long L, H;
  while(readInts(L, H)) {
    if(L > H)
      std::swap(L, H);
    unsigned int max = 0;
    long maxIndex = 0;
    for(long i = L; i <= H; ++i) {
      unsigned int val = eval(i, a);
      if(val > max) {
	max = val;
	maxIndex = i;
      }
    }
    printf("Between %li and %li, %li generates the longest sequence of %d values.\n", L, H, maxIndex, max);
  }
  return 0;
}
