#include <iostream>
#include <stdio.h>

int main() {
  while(true) {
    int N;
    std::cin >> N;
    if(N == 0)
      return 0;
    // run Kadane's algorithm:

    int max_ending_here = 0;
    int max_so_far = 0;
    for(int i = 0; i < N; ++i) {
      int x;
      std::cin >> x;
      max_ending_here = std::max(0, max_ending_here + x);
      max_so_far = std::max(max_so_far, max_ending_here);
    }
    if(max_so_far > 0)
      std::cout << "The maximum winning streak is " << max_so_far << "." << std::endl;
    else
      std::cout << "Losing streak." << std::endl;
  }
}
