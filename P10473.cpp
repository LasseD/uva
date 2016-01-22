#include <stdio.h>
#include <iostream>

unsigned long parseInt(char *s) {
  unsigned long ret = 0;
  char c;
  for(int i = 0; isprint(c = s[i]); ++i)
    ret = 10*ret + (c-'0');
  return ret;
}

unsigned long hexToInt(char c) {
  if(c >= 'a' && c <= 'f')
    return 10 + c-'a';
  if(c >= 'A' && c <= 'F')
    return 10 + c-'A';
  return c-'0';
}

unsigned long parseHex(char *s) {
  unsigned long ret = 0;
  char c;
  for(int i = 0; isprint(c = s[i]); ++i) {
    ret = 16*ret + hexToInt(c);
  }
  return ret;
}

int main() {
  char line[100];
  while(true) {
    gets(line);
    if(line[0] == '-')
      return 0;
    if(line[0] == '0' && line[1] == 'x') {
      printf("%lu\n", parseHex(&line[2]));
    }
    else {
      printf("0x%lX\n", parseInt(line));
    }
  }
}
