#include <iostream>

typedef unsigned long long ul;

int main() {
  ul a[50];
  a[0] = 1;
  a[1] = 2;
  for(int i = 2; i < 50; ++i)
    a[i] = a[i-1] + a[i-2];

  int n;
  while(true) {
    std::cin >> n;
    if(n == 0)
      return 0;
    std::cout << a[n-1] << std::endl;
  }
}
