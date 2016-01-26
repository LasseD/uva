#include <iostream>

int main() {
  long sum = 0;
  int T, A;
  std::cin >> T;
  for(int i = 0; i < T; ++i) {
    std::string s;
    std::cin >> s;
    if(s[0] == 'd') {
      std::cin >> A;
      sum += A;
    }
    else
      std::cout << sum << std::endl;
  }
  return 0;
}
