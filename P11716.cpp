#include <iostream>
#include <stdio.h>

bool isValid(char c) {
  return c == ' ' || (c >= 'A' && c <= 'Z');
}

int main() {
  char c, w[10009], out[10009];
  int cases = 0;
  gets(w);
  for(int i = 0; isdigit(c = w[i]); ++i)
    cases = 10*cases + (c-'0');
  for(int cas = 0; cas < cases; ++cas) {
    gets(w);
    int length = 0;
    while(isValid(w[length]))
      ++length;
    int root = 0;
    while(root*root < length)
      ++root;
    if(root*root != length) {
      std::cout << "INVALID" << std::endl;
    }
    else {
      out[length] = '\0';
      for(int x = 0; x < root; ++x) {
	for(int y = 0; y < root; ++y)
	  out[x*root+y] = w[y*root+x];
      }
      std::cout << out << std::endl;
    }
  }
  return 0;
}
