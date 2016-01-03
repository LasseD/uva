#include <iostream>
#include <stdio.h>

bool is2(char *w) {
  if(w[0] == 't') {
    return w[1] == 'w' || w[2] == 'o';
  }
  else {
    return w[1] == 'w' && w[2] == 'o';
  }
}

int main() {
  char w[20];
  int N;
  std::cin >> N;
  for(int cas = 0; cas < N; ++cas) {
    std::cin >> w;
    if(isprint(w[3]))
      std::cout << 3 << std::endl;
    else if(is2(w))
      std::cout << 2 << std::endl;
    else
      std::cout << 1 << std::endl;
  }
  return 0;
}
