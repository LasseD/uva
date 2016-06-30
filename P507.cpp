#include <iostream>
#include <stdio.h>

int main() {
  int N, L, x;
  std::cin >> N;
  for(int cas = 1; cas <= N; ++cas) {
    std::cin >> L;
    --L;
    // run Kadane's algorithm:

    int max_ending_here = 0;
    int max_so_far = 0;

    int start_msf = -1;
    int end_msf = 0;
    int start_meh = -1;
    for(int i = 0; i < L; ++i) {
      std::cin >> x;
      if(max_ending_here + x >= 0) {
	max_ending_here += x;
      }
      else {
	max_ending_here = 0;
	start_meh = i;
      }

      if(max_so_far < max_ending_here ||
	(max_so_far == max_ending_here && (end_msf-start_msf)<(i-start_meh))) {
	start_msf = start_meh;
	end_msf = i;
	max_so_far = max_ending_here;
      }
      //std::cerr << i << ": x=" << x << ". max here: " << max_ending_here << ", max so far: " << max_so_far << ", start msf=" << start_msf << ", start meh=" << start_meh << ", end_msf=" << end_msf << std::endl;
    }
    if(max_so_far > 0)
      std::cout << "The nicest part of route " << cas << " is between stops " << start_msf+2 << " and " << end_msf+2 << std::endl;
    else
      std::cout << "Route " << cas << " has no nice parts" << std::endl;
  }
}
