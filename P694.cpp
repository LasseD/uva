#include <iostream>

typedef long long ll;

ll lotharCollatz(ll A, ll L) {
  int terms = 0;
  while(true) {
    if(A > L)
      break;
    ++terms;
    if(A == 1)
      break;
    if(A % 2 == 0)
      A>>=1;
    else
      A = 3*A+1;
  }
  return terms;
}

int main() {
  ll L, A;
  for(int cas = 0; true; ++cas) {
    std::cin >> A >> L;
    if(A < 0 && L < 0)
      return 0;
    std::cout << "Case " << (cas+1) << ": A = " << A << ", limit = " << L << ", number of terms = " << lotharCollatz(A, L) << std::endl;
  }
}
