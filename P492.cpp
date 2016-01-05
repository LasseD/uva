#include <iostream>
#include <stdio.h>

bool isVowel(char c) {
  switch(c) {
  case 'a':
  case 'e':
  case 'i':
  case 'o':
  case 'u':
  case 'A':
  case 'E':
  case 'I':
  case 'O':
  case 'U':
    return true;
  default:
    return false;
  }
}

int main() {
  char in;
  while(EOF != (in = getchar())) {
    if(!isalpha(in)) {
      putchar(in);
      continue;
    }
    char c;
    if(isVowel(in)) {
      putchar(in);
      while(isalpha(c = getchar()))
	putchar(c);
    }
    else {
      while(isalpha(c = getchar()))
	putchar(c);
      putchar(in);
    }
    putchar('a');
    putchar('y');
    putchar(c);
  }
  return 0;
}
