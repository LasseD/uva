#include <iostream>
#include <stdio.h>

#define MAX 2147483647

typedef unsigned long long ul;

bool readInt(int &i, ul &a, char *w) {
  a = 0;
  char c;
  bool overflow = false;
  for(; isdigit(c = w[i]); ++i) {
    a = 10*a + (c-'0');
    if(a > MAX)
      overflow = true;
  }
  return overflow;
}

int main() {
  char c, w[10000];
  while(gets(w)) {
    printf("%s\n", w);
    bool mult = true;
    int i = 0;
    ul a, b;
    bool overflowA = readInt(i, a, w);
    if(overflowA)
      printf("first number too big\n");
    while(!isdigit(c = w[i])) {
      if(c == '+')
	mult = false;
      ++i;
    }
    bool overflowB = readInt(i, b, w);
    if(overflowB)
      printf("second number too big\n");
    ul result = mult ? (a*b) : (a+b);
    if(mult) {
      if(!overflowB && b == 0)
	continue;
      if(!overflowA && a == 0)
	continue;
      if(overflowA || overflowB || result > MAX)
	printf("result too big\n");
    }
    else {
      if(overflowA || overflowB || result > MAX)
	printf("result too big\n");
    }
  }
  return 0;
}
