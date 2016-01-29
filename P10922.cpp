#include <iostream>
#include <stdio.h>

int nineDegree(int n) {
  int ret = 1;
  while(n > 9) {
    int sum = 0;
    while(n > 0) {
      sum += n%10;
      n/=10;
    }
    ++ret;
    n = sum;
  }
  return ret;
}

int main() {
  char c, w[1009];
  while(true) {
    gets(w);
    if(w[0] == '0')
      return 0;
    int sum = 0;
    int i = 0;
    for(; isdigit(c = w[i]); ++i)
      sum += c-'0';
    w[i] = '\0';
    if(sum % 9 == 0) {
      printf("%s is a multiple of 9 and has 9-degree %d.\n", w, nineDegree(sum));
    }
    else {
      printf("%s is not a multiple of 9.\n", w);
    }
  }
}
