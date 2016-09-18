#include <iostream>
#include <stdio.h>

using namespace std;

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
    return 0;
  }
}

int main() {
  printf("%9s%-25sSOUNDEX CODE\n", "", "NAME");

  string s;
  char code[5];
  code[4] = '\0';

  while(cin >> s) {
    code[0] = s[0];
    int digits = 0;
    int prevCode = soundex(s[0]);
    for(unsigned int i = 0; i < s.size(); ++i) {
      int sdx = soundex(s[i]);
      if(sdx == prevCode)
	continue;
      prevCode = sdx;
      if(sdx == 0)
	continue;
      code[++digits] = '0' + sdx;
      if(digits == 3)
	break;
    }
    while(digits < 3) {
      code[++digits] = '0';
    }

    printf("%9s%-25s%s\n", "", s.c_str(), code);
  }

  printf("%19sEND OF OUTPUT\n", "");

  return 0;
}
