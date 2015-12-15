#include <iostream>
#include <stdio.h>

int main() {
  printf("Lumberjacks:\n");
  int rows, prev, curr;
  std::cin >> rows;
  for(int i = 0; i < rows; ++i) {
    bool inc = true;
    bool dec = true;
    std::cin >> prev;
    for(int j = 0; j < 9; ++j) {
      std::cin >> curr;
      inc = inc && (curr >= prev);
      dec = dec && (curr <= prev);
      prev = curr;
    }
    if(inc || dec)
      printf("Ordered\n");
    else
      printf("Unordered\n");
  }
}
