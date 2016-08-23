#include <iostream>
#include <stdio.h>
#include <algorithm>

int main() {
  int t, n, a[20000];
  std::cin >> t;
  for(int cas = 0; cas < t; ++cas) {
    std::cin >> n;
    for(int i = 0; i < n; ++i)
      std::cin >> a[i];
    std::sort(a, a+n);
    int ret = 0;
    for(int i = n-1; i >= 2; i-=3)
      ret += a[i-2];
    std::cout << ret << std::endl;
  }
}
