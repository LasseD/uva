#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void make() {
  int n = 4 + rand() % 20;

  std::cout << n << std::endl;
  for(int i = 0; i < n; ++i) {
    int XX = rand() % 200-100;
    int YY = rand() % 200-100;
    int ZZ = rand() % 200-100;
    std::cout << XX << " " << YY << " " << ZZ << std::endl;
  }
}

int main () {
  /* initialize random seed: */
  srand(time(NULL));

  for(int i = 0; i < 100; ++i)
    make();
  std::cout << 0 << std::endl;

  return 0;
}
