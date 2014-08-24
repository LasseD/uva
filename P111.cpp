#include <iostream>
#include <stdio.h>

/*
 Grading: Longest increasing subsequence
 */
typedef unsigned int uint;

int main() {
  uint n;
  std::cin >> n;

  // Create mapping:
  uint event_to_order[20] = {0}; // Events start with 1
  for(uint i = 0; i < n; ++i) {
    uint m;
    std::cin >> m;
    
    event_to_order[i] = m-1;
  }
  /*
  std::cerr << "event_to_order:" << std::endl;
  for(int k = 0; k < n; ++k) {
    std::cerr << " " << event_to_order[k];
  }
  std::cerr << std::endl;
  */
  while(true) {
    uint student[20];
    uint studentI = 0;

    for(uint i = 0; i < n; ++i) {
      uint m;
      std::cin >> m;
      if(std::cin.eof())
	return 0;
      student[m-1] = event_to_order[studentI];
      studentI++;
    }
    /*
    std::cerr << "Student order:" << std::endl;
    for(int k = 0; k < n; ++k) {
      std::cerr << " " << student[k];
    }
    std::cerr << std::endl;*/

    // Compute max increasing subsequence length:
    // Dynamic programming dp vector: dp[i,j] = Using the first i symbols, include j.
    uint dp[20*20] = {0};
    // Fix first row:
    for(uint j = 0; j < n; ++j) {
      dp[j] = 1;
    }      
    //std::cerr << "dp:" << std::endl;
    uint largest = 0;
    for(uint i = 1; i < n; ++i) {
      dp[i*20] = 1;
      //std::cerr << 1;
      for(uint j = 1; j < n; ++j) { // j is symbol location
	uint maxLengthWithLessSymbols = dp[(i-1)*20+j];

	uint largestInRow = 0;
        for(int k = 0; k < j; ++k) {
	  if(dp[(i-1)*20+k] > largestInRow && student[k] < student[j])
	    largestInRow = dp[(i-1)*20+k];
        }	

        dp[i*20+j] = std::max(maxLengthWithLessSymbols,largestInRow+1);
	if(largest < dp[i*20+j])
	  largest = dp[i*20+j];
	//	std::cerr << " " << dp[i*20+j];
      }      
      //      std::cerr << std::endl;
    }
        std::cout << largest << std::endl;
  }
}
