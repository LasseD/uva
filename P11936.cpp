#include <iostream>
#include <algorithm>

int main() {
  int n, a[3];
  std::cin >> n;
  for(int cas = 0; cas < n; ++cas) {
    std::cin >> a[0] >> a[1] >> a[2];
    std::sort(a, a+3);
    if(a[0]+a[1] <= a[2])
      std::cout << "Wrong!!" << std::endl;
    else
      std::cout << "OK" << std::endl;
  }
  return 0;
}
