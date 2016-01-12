#include <iostream>

#define MAX 9999999

int main() {
  long N, B, H, W, p, a;
  while(std::cin >> N >> B >> H >> W) {
    long lowest = MAX;
    for(long i = 0; i < H; ++i) {
      std::cin >> p;
      for(long j = 0; j < W; ++j) {
	std::cin >> a;
	if(a >= N && p*N < lowest)
	  lowest = p*N;
      }
    }
    if(lowest > B)
      std::cout << "stay home" << std::endl;
    else
      std::cout << lowest << std::endl;
  }
  return 0;
}
