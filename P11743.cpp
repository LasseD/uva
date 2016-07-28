#include <iostream>
#include <stdio.h>

int main() {
  char c, w[39];
  gets(w);
  int lines = 0;
  for(int i = 0; isprint(c = w[i]); ++i) {
    lines = 10*lines + (c-'0');
  }
  
  for(int cas = 0; cas < lines; ++cas) {
    gets(w);
    int add, sum = 0;
    bool even = true;
    for(int i = 0; isprint(c = w[i]); ++i) {
      if(!isdigit(c))
	continue;
      if(even) {
	add = 2*(c-'0');
	while(add > 0) {
	  sum += add%10;
	  add/=10;
	}
      }
      else {
	add = (c-'0');
	sum += add;
      }
      even = !even;
    }

    if((sum % 10) == 0)
      std::cout << "Valid" << std::endl;
    else
      std::cout << "Invalid" << std::endl;
  }
  return 0;
}
