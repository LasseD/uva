#include <iostream>
#include <cstdlib>

/*
1: 0
2: 01, 10
3: 010, 101
4: 0101, 1001, 1010 => 
5: 01001, 01010, 10010, 10101 => 

New: 
- prev ending on 0 => prev+1
- prev ending on 1 => prev+0
- prev prev ending on 0 => prevprev+01
*/
int main() {
  unsigned int ending0[76], ending1[76];
  // 0:
  ending0[0] = 1;
  ending1[0] = 0;
  // 1:
  ending0[1] = 1;
  ending1[1] = 1;
  // 2:
  ending0[2] = 1;
  ending1[2] = 1;
  // 3+
  for(int i = 3; i < 76; ++i) {
    ending0[i] = ending1[i-1];
    ending1[i] = ending0[i-1] + ending0[i-2];
  }

  std::string line;
  while(getline(std::cin, line)) {
    int in = atoi(line.c_str());
    unsigned int out = ending0[in-1] + ending1[in-1];
    std::cout << out << std::endl;
  }
  return 0;
}
