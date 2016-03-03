#include <iostream>
#include <math.h>

typedef unsigned long long ul;

/*
n-gon / number of diagonals N:
4 / 2
5 / 5
6 / 9
n / (n-1)+(n-2)+(n-3)+... - n = (n-1)*n/2-n
N = (n-1)*n/2-n = (n-3)*n/2 = (n^2-3n)/2 => 
n^2 - 3n - 2N = 0 =>
n = (3 + sqrt(9+8N))/2
 */
int main() {
  ul N;
  for(int cas = 1; true; ++cas) {
    std::cin >> N;
    if(N == 0)
      return 0;
    ul n = 1+(ul)(-0.000005+(3+sqrt(9+8*(double)N))/2);
    std::cout << "Case " << cas << ": " << n << std::endl;
  }
}
