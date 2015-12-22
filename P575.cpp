#include <iostream>
#include <stdio.h>

#define LEN 1000

unsigned long evalSkewBinary(char *line) {
  int i = 0;
  while(isdigit(line[i])) {
    ++i;
  }
  --i;
  unsigned long twoK1 = 2;
  unsigned long sum = 0;
  while(i >= 0) {
    sum += (line[i]-'0')*(twoK1-1);
    twoK1*=2;
    --i;
  }
  return sum;
}

int main() {
  char line[LEN];
  while(true) {
    std::cin.getline(line, LEN);
    unsigned long n = evalSkewBinary(line);
    if(n == 0)
      return 0;
    std::cout << n << std::endl;
  }
}
