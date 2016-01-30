#include <stdio.h>
#include <iostream>

int readInt(char *w) {
  char c;
  int ret = 0;
  for(int i = 0; isdigit(c = w[i]); ++i)
    ret = 10*ret + (c-'0');
  return ret;
}

int main() {
  char w[90];
  gets(w);
  int N = readInt(w);
  for(int cas = 0; cas < N; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    gets(w);
    gets(w);
    // Find length:
    int len = 0;
    while(isprint(w[len]))
      ++len;

    // Find period:
    for(int period = 1; period <= len; ++period) {
      if(len % period != 0)
	continue;
      bool ok = true;
      for(int i = period; i < len; ++i) {
	if(w[i] != w[i-period]) {
	  ok = false;
	  break;
	}	  
      }
      if(ok) {
	std::cout << period << std::endl;
	break;
      }
    }
  }
  return 0;
}
