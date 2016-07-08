#include <stdio.h>
#include <iostream>
#include <algorithm>

typedef std::string String;

bool cmp(String &a, String &b) { 
  unsigned int size = a.size() + b.size();
  
  for(unsigned int i = 0; i < size; ++i) {
    char c1 = i < a.size() ? a[i] : b[i-a.size()];
    char c2 = i < b.size() ? b[i] : a[i-b.size()];
    if(c1 != c2)
      return c1 > c2;
  }
  return a.size() < b.size();
}

int main() {
  String numbers[50];
  int N;

  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    for(int i = 0; i < N; ++i)
      std::cin >> numbers[i];
    std::sort(numbers, numbers+N, cmp);
    for(int i = 0; i < N; ++i)
      std::cout << numbers[i];
    std::cout << std::endl;
  }
}
