#include <iostream>
#include <stdio.h>

int main() {
  int S;
  std::cin >> S;
  for(int set = 0; set < S; ++set) {
    bool anyZero = false;
    int a;
    for(int i = 0; i < 13; ++i) {
      std::cin >> a;
      if(a == 0)
	anyZero = true;
    }
    if(anyZero)
      printf("Set #%d: No\n", set+1);
    else
      printf("Set #%d: Yes\n", set+1);
  }
  return 0;
}
