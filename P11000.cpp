#include <iostream>

#define YEARS 50

typedef unsigned long long ul;

int main() {
  ul males[YEARS], females[YEARS];
  males[0] = 0;
  females[0] = 1;
  for(int i = 1; i < YEARS; ++i) {
    males[i] = males[i-1] + females[i-1];
    females[i] = 1 + males[i-1];
  }
  int N;
  while(true) {
    std::cin >> N;
    if(N == -1)
      return 0;
    std::cout << males[N] << " " << (males[N]+females[N]) << std::endl;
  }
}
