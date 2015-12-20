#include <iostream>
#include <vector>

int main() {
  int N, L, M[50];
  std::cin >> N;
  for(int ignore = 0; ignore < N; ++ignore) {
    std::cin >> L;
    int swaps = 0;
    for(int i = 0; i < L; ++i)
      std::cin >> M[i];
    for(int i = 0; i < L; ++i) {
      int j = 0;
      while(M[j] != i+1) {
	if(M[j] > i+1)
	  ++swaps;
	++j;
      }
    }
    std::cout << "Optimal train swapping takes " << swaps << " swaps." << std::endl;
  }
}
