#include <iostream>

typedef unsigned long long ul;

ul expMod(ul B, ul P, ul M) {
  if(P == 0)
    return M == 1 ? 0 : 1;
  ul em = expMod(B, P/2, M);
  if(P%2 == 1)
    return (B*em*em)%M;
  return (em*em)%M;
}

int main() {
  ul B, P, M;
  while(std::cin >> B >> P >> M) {
    std::cout << expMod(B, P, M) << std::endl;
  }
  return 0;
}
