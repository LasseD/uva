#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

bool leap(ul N) {
  if(N % 4 != 0)
    return false;
  if(N % 100 != 0)
    return true;
  return N % 400 == 0;
}

bool isH(ul N) {
  return 
}

int main() {
  ul N;
  while(std::cin >> N) {
    
  }
  return 0;
}
