#include <iostream>
#include <ctype.h>

#define LIST_SIZE 100001

int main() {
  int n, k, m;

  std::cin >> n >> k;

  int listMax = 0;
  int list[LIST_SIZE];
  for(int i = 0; i < LIST_SIZE; ++i) {
    list[i] = 0;
  }

  for(int i = 0; i < n; ++i) {
    std::cin >> m;
    list[m]++;
  }
  
  int count = 0;
  int max = 0;
  for(int i = 0; i < LIST_SIZE; ++i) {
    count += list[i];
    if(i >= 1000) {
      count -= list[i-1000];
    }
    int maybeMax = (count+k-1)/k;
    if(maybeMax > max) {
      max = maybeMax;
    }
    //std::cerr<<"Maybe max " << maybeMax <<std::endl;
  }
  std::cout << max << std::endl;
}
