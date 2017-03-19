#include <iostream>
#include <cmath>

int main() {
  std::string a, b;
  std::cin >> a >> b;
  int endA = a.size()-1;
  int endB = b.size()-1;
  while(a[endA] == b[endB]) {
    if(endA == 0) {
      std::cout << endB << std::endl;
      return 0;
    }
    if(endB == 0) {
      std::cout << 0 << std::endl;
      return 0;
    }
    --endA;
    --endB;
  }
  int begin = 0;
  while(a[begin] == b[begin]) {
    if(begin == endB){
      std::cout << 0 << std::endl;
      return 0;
    }
    if(begin == endA){
      std::cout << (b.size()-a.size()) << std::endl;
      return 0;
    }
    ++begin;
  }
  std::cout << (endB-begin+1) << std::endl;
  return 0;
}
