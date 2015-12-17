#include <iostream>
#include <stdio.h>

int main() {
  int T, N;
  long long M[10000];
  char c;
  std::cin >> T;

  for(int test = 0; test < T; ++test) {
    std::cin >> c >> c >> N;
    for(int x = 0; x < N; ++x) {
      for(int y = 0; y < N; ++y) {
	std::cin >> M[x*N+y];
      }
    }
    bool symmetric = true;
    for(int x = 0; x < N; ++x) {
      for(int y = 0; y < N; ++y) {
	if(M[x*N+y] < 0 || M[x*N+y] != M[(N-1-x)*N+(N-1-y)]) {
	  symmetric = false;
	  break;
	}
      }
      if(!symmetric)
	break;
    }
    if(symmetric)
      printf("Test #%d: Symmetric.\n", test+1);
    else
      printf("Test #%d: Non-symmetric.\n", test+1);
  }
  return 0;
}
