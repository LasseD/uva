#include <iostream>

typedef long long ll;

int main() {
  ll a, b, c, d, L;
  while(true) {
    std::cin >> a >> b >> c >> d >> L;
    if((a | b | c | d | L) == 0)
      return 0;
    int ret = 0;
    for(int x = 0; x <= L; ++x) {
      ll fx = a*x*x+b*x+c;
      if(fx % d == 0)
	++ret;
    }
    std::cout << ret << std::endl;
  }
}
