#include <iostream>

/*
Pizza slicing:
0 => 1  = (0+1)*0/2+1
1 => 2  = (1+1)*1/2+1
2 => 4
3 => 7  = (3+1)*3/2+1
4 => 11 = (4+1)*4/2+1
5 => 16 = (5+1)*5/2+1
n => 
 */
int main() {
  while(true) {
    long n;
    std::cin >> n;
    if(n < 0)
      return 0;
    std::cout << ((n+1)*n/2+1) << std::endl;
  }
}
