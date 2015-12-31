#include <iostream>

typedef unsigned long long ul;

int main() {
  ul N;
  while(std::cin >> N) {
    ul numberOfLinesAbove = N/2;
    ul numbersAbove = (N-1)*(numberOfLinesAbove/2);
    if(numberOfLinesAbove % 2 == 1)
      numbersAbove += N/2;
    ul lastNumber = (numbersAbove+N-1)*2+1;
    ul sum = 3*lastNumber-6;
    std::cout << sum << std::endl;
  }
  return 0;
}
