#include <iostream>
#include <stdio.h>

int soundex(char c) {
  switch(c) {
  case 'B':
  case 'F':
  case 'P':
  case 'V':
    return 1;
  case 'C':
  case 'G':
  case 'J':
  case 'K':
  case 'Q':
  case 'S':
  case 'X':
  case 'Z':
    return 2;
  case 'D':
  case 'T':
    return 3;
  case 'L':
    return 4;
  case 'M':
  case 'N':
    return 5;
  case 'R':
    return 6;
  default:
    return -1;
  }
}

int main() {
  char c, line[250];
  while(gets(line)) {
    int prev = -1;
    for(int i = 0; isprint(c = line[i]); ++i) {
      int sdx = soundex(c);
      if(sdx == prev)
	continue;
      prev = sdx;
      if(sdx == -1)
	continue;
      std::cout << ((char)(sdx+'0'));
    }
    std::cout << std::endl;
  }
  return 0;
}
