#include <iostream>

int main() {
  while(true) {
    int N, prevprev, prev, first, second;
    std::cin >> N;
    if(N == 0)
      return 0;
    std::cin >> first >> second;
    prev = second;
    prevprev = first;
    
    int ret = 0;
    for(int i = 2; i < N; ++i) {
      int curr;
      std::cin >> curr;
      
      if((prevprev < prev) == (curr < prev)) {
        ++ret;
      }
    
      prevprev = prev;
      prev = curr;
    }
    // peak at loop end:
    if((prevprev < prev) == (first < prev)) {
	//std::cerr << "End peak!" << std::endl;
      ++ret;
    }
    // peak at loop start:
    if((first < second) == (first < prev)) {
	//std::cerr << "Start peak!" << std::endl;
      ++ret;
    }
    
    std::cout << ret << std::endl;
  }
}
