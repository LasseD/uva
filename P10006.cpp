#include <iostream>
#include <stdio.h>

/*
Precompute the Carmichael numbers - they take to long to check.
 */
int main() {
  int carmichael[] = {561, 1105, 1729, 2465, 2821, 6601, 8911, 10585, 15841, 29341, 41041, 46657, 52633, 62745, 63973, -1};
  int n, m;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    bool done = false;
    for(int i = 0; (m = carmichael[i]) != -1; ++i) {
      if(m == n) {
	printf("The number %d is a Carmichael number.\n", m);
	done = true;
      }
    }
    if(!done)
      printf("%d is normal.\n", n);
  }
}
