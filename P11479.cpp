#include <iostream>
#include <algorithm>

int main() {
  long T, a[3];
  std::cin >> T;
  for(long cas = 0; cas < T; ++cas) {
    std::cin >> a[0] >> a[1] >> a[2];
    std::sort(a, a+3);
    
    std::cout << "Case " << (cas+1) << ": ";
    if(a[0] <= 0 || a[0] + a[1] <= a[2])
      std::cout << "Invalid" << std::endl;
    else if(a[0] == a[2])
      std::cout << "Equilateral" << std::endl;
    else if(a[0] == a[1] || a[1] == a[2])
      std::cout << "Isosceles" << std::endl;
    else
      std::cout << "Scalene" << std::endl;
  }
  return 0;
}
