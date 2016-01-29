#include <iostream>

int main() {
  int m1, h1, m2, h2;
  while(true) {
    std::cin >> h1 >> m1 >> h2 >> m2;
    if(h1 == 0 && m1 == 0 && h2 == 0 && m2 == 0)
      return 0;

    int diffH = h2-h1;
    int diffM = m2-m1;
    if(diffM < 0) {
      diffM += 60;
      --diffH;
    }      
    if(diffH < 0)
      diffH+=24;

    std::cout << (60*diffH+diffM) << std::endl;
  }
}
