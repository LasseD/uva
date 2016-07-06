#include <stdio.h>
#include <iostream>

int main() {
  char *w = new char[1000009];
  bool *possiblePeriods = new bool[1000001];
  while(true) {
    gets(w);
    // Find length:
    int len = 0;
    while(isprint(w[len]))
      ++len;
    if(len == 1 && w[0] == '.')
      break;
    if(len == 0) {
      std::cout << "0" << std::endl;
      continue;
    }
    w[len] = '\0';
    //std::cerr << "len=" << len << ", w=" << w << std::endl;

    //memset(possiblePeriods, true, len+1);
    for(int i = 1; i < len; ++i) {
      possiblePeriods[i] = len%i == 0;
    }      

    // Find period:
    int best = 1;
    for(int period = len-1; period >= 1; --period) {
      if(!possiblePeriods[period])
	continue;
      bool ok = true;
      for(int i = period; i < len; ++i) {
	if(w[i] != w[i-period]) {
	  ok = false;
	  break;
	}	  
      }
      if(ok) {
	//std::cerr << "Found best period=" << period << std::endl;
	best = len/period;
      }
      else {
	for(int smaller = 2; smaller < period; ++smaller)
	  if(period % smaller == 0)
	    possiblePeriods[smaller] = false;
      }
    }
    std::cout << best << std::endl;
  }
  delete[] possiblePeriods;
  delete[] w;
  return 0;
}
