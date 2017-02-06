#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void make() {
  int n = 2 + rand() % 20;
  int m = rand() % 40;

  std::cout << n << " " << m << std::endl;
  for(int i = 0; i < m; ++i) {
    int XX = rand() % n;
    int YY = rand() % n;
    std::cout << XX << " " << YY << std::endl;
  }
}

int main () {
  /* initialize random seed: */
  srand(time(NULL));

  //for(int i = 0; i < 1000; ++i)
    make();

  return 0;
}
