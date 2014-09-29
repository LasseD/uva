#include <iostream>

int main() {
  int caseNum = 1;
  int problems[13];
  while(true) {
    int N;
    std::cin >> N;
    if(N < 0)
      return 0;
    for(int i = 1; i < 12; ++i) {
      problems[i] = 0;
    }
    problems[0] = N;
    
    // Read new problems:
    for(int i = 0; i < 12; ++i) {
      int m;
      std::cin >> m;
      problems[i+1] = m + problems[i];
    }

    // Read usage:
    std::cout << "Case " << (caseNum++) << ":" << std::endl;
    int used = 0;
    for(int i = 0; i < 12; ++i) {
      int m;
      std::cin >> m;
      if(m == 0 || m+used <= problems[i]) {
	std::cout << "No problem! :D" << std::endl;
	used += m;
      }
      else
	std::cout << "No problem. :(" << std::endl;
    }
  }
}
