#include <iostream>
#include <stdio.h>

int main() {
  int N, M;
  while(true) {
    std::cin >> N >> M;
    if(N == 0 && M == 0)
      return 0;
    int *a = new int[N];
    int *b = new int[M];
    for(int i = 0; i < N; ++i)
      std::cin >> a[i];
    for(int i = 0; i < M; ++i)
      std::cin >> b[i];
    int ret = 0;
    int iA = 0;
    for(int iB = 0; iB < M; ++iB) {
      while(iA < N-1 && a[iA] < b[iB])
	++iA;
      if(a[iA] == b[iB])
	++ret;
    }
    std::cout << ret << std::endl;
  }
}
