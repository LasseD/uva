#include <iostream>
#include <stdio.h>

int main() {
  int K, N, M, X, Y;
  while(true) {
    std::cin >> K;
    if(K == 0)
      return 0;
    std::cin >> N >> M;
    for(int i = 0; i < K; ++i) {
      std::cin >> X >> Y;
      if(X == N || Y == M)
	std::cout << "divisa" << std::endl;
      else if(X < N && Y < M)
	std::cout << "SO" << std::endl;
      else if(X < N && Y > M)
	std::cout << "NO" << std::endl;
      else if(X > N && Y > M)
	std::cout << "NE" << std::endl;
      else
	std::cout << "SE" << std::endl;
    }
  }
}
