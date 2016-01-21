#include <iostream>

int main() {
  int T, relevance[10];
  std::string s[10];
  std::cin >> T;
  for(int cas = 1; cas <= T; ++cas) {
    int max = 0;
    for(int i = 0; i < 10; ++i) {
      std::cin >> s[i] >> relevance[i];
      if(relevance[i] > max)
	max = relevance[i];
    }
    std::cout << "Case #" << cas << ":" << std::endl;
    for(int i = 0; i < 10; ++i) {
      if(relevance[i] == max)
	std::cout << s[i] << std::endl;
    }
  }
  return 0;
}
