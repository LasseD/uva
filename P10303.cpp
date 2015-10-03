#include <iostream>
#include <sstream>

int main() {
  unsigned long long lookup[1001];
  lookup[0] = lookup[1] = 1;
  for(unsigned int i = 2; i <= 1000; ++i) {
    lookup[i] = 0;
    for(unsigned int j = 0; j <= i-1; ++j) {
      unsigned long long left = lookup[j];
      unsigned long long right = lookup[i-1-j];
      lookup[i] += left*right;
    }
  }

  std::string line;
  while(getline(std::cin, line)) {
    std::stringstream ss(line);
    int i;
    ss >> i;
    std::cout << lookup[i] << std::endl;
  }
  return 0;
}
