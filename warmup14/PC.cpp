#include <iostream>
#include <cmath>

/*
an...a1a0 X = an-1...a0an
SUM(0,n,10^i*ai) * X = an+10*SUM(0,n-1,10^i*ai)
SUM(0,n,10^i*ai) * X = an+10*(SUM(0,n,10^i*ai)-10^n*an)
a*X = an+10*(a-10^n*an)
a*X = an+10a-10^(n+1)*an
a*X = 10a+(1-10^(n+1))an
(X-10)a = (1-10^(n+1))an

since 0 < an <= 9:
iterate 0<=n<=8
 */
int main() {
  double X;
  std::cin >> X;
  
  long long tenn = 1;
  bool any = false;
  for(int n = 0; n <= 8; ++n) {
    for(int an = 1; an <= 9; ++an) {
      long long a = round(((10*tenn-1)*an)/(10-X));
      long long shift = 10*(a-tenn*(a/tenn))+an;
      // check:
      //std::cerr << "X=" << X << ", a=" << a << ", an=" << an << ", 10^n=" << tenn << ", shift=" << shift << std::endl;
      if(a >= 1 &&
	 shift >= 1 &&
	 a < 100000000 && 
	 an == a/tenn && 
	 round((X*a-shift)*10000) == 0) {
	std::cout << a << std::endl;
	any = true;
      }
    }
    tenn*=10;
  }
  if(!any)
    std::cout << "No solution" << std::endl;
  
  return 0;
}
