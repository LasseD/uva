#include <iostream>
#include <stdio.h>
#include <iomanip>

int main() {
  long double vals[6];
  for(int i = 0; i < 6; ++i) {
    std::cin >> vals[i];
  }
  int masks[6];
  masks[0] = 1;
  for(int i = 1; i < 6; ++i) {
    masks[i] = masks[i-1]<<1;
  }
  printf("%i\n", 1+0x3F);
  for(int i = 0; i <= 0x3F; ++i) {
    for(int j = 0; j < 6; ++j) {
      if(j != 0)
	printf(" ");
      if((masks[j] & i) == masks[j]) {
	printf("%.9Lf", vals[j]);;
      }
      else {
	printf("-1");
      }
    }
    printf("\n");
  }
}
