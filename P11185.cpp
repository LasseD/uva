#include <iostream>
#include <stdio.h>
#include <stack>

void printTernary(long long n) {
  if(n == 0) {
    std::cout << "0" << std::endl;
    return;
  }
  std::stack<char> s;
  while(n > 0) {
    s.push('0' + (n%3));
    n/=3;
  }
  while(!s.empty()) {
    std::cout << s.top();
    s.pop();
  }
  std::cout << std::endl;
 }

int main() {
  long long N;
  while(true) {
    std::cin >> N;
    if(N < 0)
      return 0;
    printTernary(N);
  }
}
