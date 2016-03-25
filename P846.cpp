#include <iostream>
#include <math.h>

/*
1+2+...m = m(m+1)/2 = Q => 
M = m+½ => 2Q = (M+½)(M-½) = M^2-1/4 =>
sqrt(2Q+1/4) = M => m = sqrt(2Q+1/4)-½
 */
int main() {
  long N, x, y, m;
  std::cin >> N;
  for(long cas = 0; cas < N; ++cas) {
    std::cin >> x >> y;
    if(x > y)
      std::swap(x,y);
    m=y-x; // only use 0-m:
    long M = (long)(sqrt(m+0.25)-0.5); // longest step.
    long halfPath = M*(M+1)/2;

    if(2*halfPath > m) {
      int* die = NULL;
      die[42] = 666;
    }
      
    long gap = m-2*halfPath;
    //std::cerr << m << ": M=" << M << ", half path=" << halfPath << ", gap=" << gap << std::endl;
    std::cout << (2*M + (gap+M)/(M+1)) << std::endl;
  }
}
