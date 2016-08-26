#include <iostream>
#include <stdio.h>

int main() {
  int n;
  char c;
  while(true) {
    scanf("%d\n", &n);
    if(n == 0)
      return 0;
    int minDist = 20000000;
    int lastR = -20000000;
    int lastD = -20000000;
    int idx = 0;
    for(int j = 0; j < n; ++j) {
      c = getchar();
      ++idx;
      switch(c) {
      case 'R':
	if(idx-lastD < minDist)
	  minDist = idx-lastD;
	lastR = idx;
	break;
      case 'D':
	if(idx-lastR < minDist)
	  minDist = idx-lastR;
	lastD = idx;
	break;
      case 'Z':
	minDist = 0;
	break;
      default:
	break;
      }
    }
    std::cout << minDist << std::endl;
  }
}
