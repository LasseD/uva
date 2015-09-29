#include <iostream>
#include <stdio.h>
#include <algorithm>

#define ABS(a) ((a) < 0 ? -(a) : (a))

int main() {
  int n;
  int vals[3000];
  while(std::cin >> n) {
    for(int i = 0; i < n; ++i) {
      std::cin >> vals[i];
    }
    if(n == 0)
      std::cout << "Not jolly" << std::endl;
    else if(n == 1)
      std::cout << "Jolly" << std::endl;
    else {
      // First turn vals into diffs:
      int prev = vals[0];
      for(int i = 1; i < n; ++i) {
	int val = vals[i];
	vals[i] = ABS(val-prev);
	//std::cerr << " " << vals[i];
	prev = val;
      }
      //std::cerr << std::endl;
      // Now sort:
      std::sort(&vals[1], &vals[n]);
      // Checkk:
      bool ok = true;
      for(int i = 1; i < n; ++i) {
	if(vals[i] != i) {
	  ok = false;
	  break;
	}
      }
      if(!ok)
	std::cout << "Not jolly" << std::endl;
      else
	std::cout << "Jolly" << std::endl;
    }
  }
}
