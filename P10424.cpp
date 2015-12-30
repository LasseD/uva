#include <iostream>
#include <stdio.h>

int wordSum(char *l) {
  int ret = 0;
  char c;
  for(int i = 0; isprint(c = l[i]); ++i) {
    if(c >= 'a' && c <= 'z')
      ret += (int)(c-'a')+1;
    else if(c >= 'A' && c <= 'Z')
      ret += (int)(c-'A')+1;
  }
  return ret;
}

int truncateInt(int a) {
  while(a > 9) {
    int b = 0;
    while(a > 0) {
      b += (a%10);
      a /= 10;
    }
    a = b;
  }
  return a;
}

int main() {
  char l1[30], l2[30];
  while(gets(l1)) {
    gets(l2);
    int a = truncateInt(wordSum(l1));
    int b = truncateInt(wordSum(l2));
    if(a < b)
      printf("%.2f %%\n", 100*a/(double)b);
    else
      printf("%.2f %%\n", 100*b/(double)a);
  }
  return 0;
}
