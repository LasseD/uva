#include <iostream>
#include <stdio.h>

int main() {  
  printf("PERFECTION OUTPUT\n");
  int n;
  while(true) {
    std::cin >> n;
    if(n == 0) {
      printf("END OF OUTPUT\n");
      return 0;
    }
    if(n <= 3) {
      printf("    1  DEFICIENT\n");
      continue;
    }    
    int sum = 1;
    for(int i = 2; i*2 <= n; ++i) {
      if((n/i)*i == n) {
	//printf("(%d)", i);
	sum += i;
      }
    }
    
    if(sum == n)
      printf("%5d  PERFECT\n", n);
    else if(sum < n)
      printf("%5d  DEFICIENT\n", n);
    else
      printf("%5d  ABUNDANT\n", n);
  }
}
