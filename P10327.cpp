#include <iostream>
#include <algorithm>

typedef std::pair<long,int> pair;

int main() {
  int L;
  pair M[1000], C[1000];
  while(std::cin >> L) {
    int swaps = 0;
    for(int i = 0; i < L; ++i) {
      long item;
      std::cin >> item;
      M[i] = C[i] = pair(item, i);
    }
    std::sort(M, M+L);
    for(int i = 0; i < L; ++i) {
      for(int j = 0; j < M[i].second; ++j) {
	if(C[j].first > M[i].first)
	  ++swaps;
      }
    }
    std::cout << "Minimum exchange operations : " << swaps << std::endl;
  }
}
