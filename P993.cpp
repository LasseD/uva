#include <iostream>
#include <stdio.h>
#include <stack>

int main() {
  unsigned long N;
  int cases;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    std::cin >> N;
    if(N <= 9) {
      std::cout << N << std::endl;
      continue;
    }
    std::stack<int> s;
    for(int i = 9; i >= 2; --i) {
      while(N % i == 0) {
	s.push(i);
	N/=i;
      }      
    }
    if(N != 1)
      std::cout << -1 << std::endl;
    else {
      while(!s.empty()) {
	std::cout << s.top();
	s.pop();
      }
      std::cout << std::endl;
    }    
  }
  return 0;
}
