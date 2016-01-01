#include <iostream>

int main() {
  int n, a, b, c;
  std::cin >> n;
  for(int cas = 0; cas < n; ++cas) {
    std::cin >> a >> b >> c;
    std::cout << "Case " << (cas+1) << ": ";
    if(a > 20 || b > 20  || c > 20)
      std::cout << "bad" << std::endl;
    else
      std::cout << "good" << std::endl;
  }
  return 0;
}
