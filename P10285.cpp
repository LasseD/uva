#include <iostream>
#include <stdio.h>

int main() {
  int N, R, C, heights[10000], runs[10000]; // idx y*C+x
  std::string s;
  std::cin >> N;
  for(int cas = 1; cas <= N; ++cas) {
    std::cin >> s >> R >> C; // r lines:
    for(int y = 0; y < R; ++y) {
      for(int x = 0; x < C; ++x) {
	int idx = y*C+x;
	std::cin >> heights[idx];
	runs[idx] = 1;
      }
    }

    int longestRun = 1;
    bool improved = true;
    while(improved) {
      improved = false;
      for(int y = 0; y < R; ++y) {
	for(int x = 0; x < C; ++x) {
	  int idx = y*C+x;
	  if(x > 0 && heights[y*C+x-1] < heights[idx] && runs[y*C+x-1]+1 > runs[idx]) {
	    improved = true;
	    runs[idx] = runs[y*C+x-1]+1;
	  }
	  if(x < C-1 && heights[y*C+x+1] < heights[idx] && runs[y*C+x+1]+1 > runs[idx]) {
	    improved = true;
	    runs[idx] = runs[y*C+x+1]+1;
	  }
	  if(y > 0 && heights[(y-1)*C+x] < heights[idx] && runs[(y-1)*C+x]+1 > runs[idx]) {
	    improved = true;
	    runs[idx] = runs[(y-1)*C+x]+1;
	  }
	  if(y < R-1 && heights[(y+1)*C+x] < heights[idx] && runs[(y+1)*C+x]+1 > runs[idx]) {
	    improved = true;
	    runs[idx] = runs[(y+1)*C+x]+1;
	  }

	  if(runs[idx] > longestRun)
	    longestRun = runs[idx];
	} // for x
      } // for y
    } // while improved
    std::cout << s << ": " << longestRun << std::endl;
  }
  return 0;
}
