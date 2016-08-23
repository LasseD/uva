#include <iostream>
#include <stdio.h>
#include <algorithm>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))

int main() {
  int t, ant, pole, n;
  std::cin >> t;
  for(int cas = 0; cas < t; ++cas) {
    std::cin >> pole >> n;
    int min = 0;
    int max = 0;
    for(int i = 0; i < n; ++i) {
      std::cin >> ant;
      int walkUp = pole-ant;
      min = MAX(min, MIN(ant, walkUp));
      max = MAX(max, MAX(ant, walkUp));
    }
    std::cout << min << " " << max << std::endl;
  }
}
