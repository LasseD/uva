#include <iostream>
#include <stdio.h>

int main() {
  int step, mod;
  while(std::cin >> step >> mod) {
    int s = step % mod;
    int idx = 0;
    bool good = true;
    for(int i = 0; i < mod-1; ++i) {
      idx+=s;
      if(idx >= mod)
	idx-=mod;
      if(idx == 0) {
	good = false;
	break;
      }
    }
    if(good) {
      idx+=s;
      good = (idx == mod); // == 0
    }

    printf("%10d%10d    ", step, mod);
    if(good)
      printf("Good Choice\n\n");
    else
      printf("Bad Choice\n\n");
  }
}
