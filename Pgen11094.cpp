#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void make(int M, int N, char m[][20], int X, int Y) {
  std::cout << M << " " << N << std::endl;
  for(int x = 0; x < M; ++x) {
    for(int y = 0; y < N; ++y) {
      std::cout << m[x][y];
    }
    std::cout << std::endl;
  }
  std::cout << X << " " << Y << std::endl;
}

int main () {
  /* initialize random seed: */
  srand(time(NULL));

  int N = 1+rand()%10;
  int M = 1+rand()%10;
  char m[20][20];

  for(int y = 0; y < N; ++y) {
    for(int x = 0; x < M; ++x) {
      m[x][y] = rand() % 2 == 1 ? 'X' : ' ';
    }
  }

  
  for(int y = 0; y < N; ++y) {
    for(int x = 0; x < M; ++x) {
      make(M, N, m, x, y);
    }
  }//*/
  //make(M, N, m, 0, 0);

  return 0;
}
