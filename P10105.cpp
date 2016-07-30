#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

ul fac(int b) {
  ul ret = 1;
  for(int i = 2; i <= b; ++i)
    ret *= i;
  return ret;
}

/*
Compute coefficient.
See:
https://en.wikipedia.org/wiki/Multinomial_theorem
https://en.wikipedia.org/wiki/Multiindices

So (x1+...xm)^n = SUM_(|A|=n)(binom(n,A)x^A)
where A=(A1,...,Am) and x^A=x1^A1*...*xm^Am
Recall binom(n,A) = n!/(A1!A2!...Am!)
 */
int main() {
  int n, k, a;
  while(std::cin >> n >> k) {
    ul out = fac(n);
    for(int i = 0; i < k; ++i) {
      std::cin >> a;
      out /= fac(a);
    }
    std::cout << out << std::endl;
  }
  return 0;
}
