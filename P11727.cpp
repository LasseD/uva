#include <iostream>
#include <algorithm>

int main() {
  int T, s[3];
  std::cin >> T;
  for(int ignore = 0; ignore < T; ++ignore) {
    std::cin >> s[0] >> s[1] >> s[2];
    std::sort(s, s+3);
    std::cout << "Case " << (ignore+1) << ": " << s[1] << std::endl;
  }
}
