#include <iostream>
#include <stdio.h>

int countKeypressesForChar(char c) {
  switch(c) {
  case 'a':
  case 'd':
  case 'g':
  case 'j':
  case 'm':
  case 'p':
  case 't':
  case 'w':
  case ' ':
    return 1;
  case 'b':
  case 'e':
  case 'h':
  case 'k':
  case 'n':
  case 'q':
  case 'u':
  case 'x':
    return 2;
  case 'c':
  case 'f':
  case 'i':
  case 'l':
  case 'o':
  case 'r':
  case 'v':
  case 'y':
    return 3;
  default:
    return 4;
  }
}

int countKeypressesForWord(char *s) {
  int sum = 0;
  char c;
  for(int i = 0; isprint(c = s[i]); ++i) {
    sum += countKeypressesForChar(c);
  }
  return sum;
}

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return ret;
}

int main() {
  char w[109];
  unsigned int cases = readUInt();
  for(unsigned int cas = 1; cas <= cases; ++cas) {
    gets(w);
    std::cout << "Case #" << cas << ": " << countKeypressesForWord(w) << std::endl;
  }
  return 0;
}
