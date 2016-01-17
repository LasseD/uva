#include <iostream>
#include <stdio.h>

#define LEN 750

long step(long a) {
  //std::cerr << a;
  long sumSquares = 0;
  while(a > 0) {
    long digit = a%10;
    sumSquares += digit*digit;
    a/=10;
  }
  //std::cerr << "->" << sumSquares << std::endl;
  return sumSquares;
}

bool happy(const long n, unsigned int *a) {
  if(n < LEN && a[n] != 0)
    return a[n] == 1;
  long mm = n < LEN ? n : step(n);
  long m = mm;
  while(m != 1 && a[m] == 0) {
    a[m] = 3;
    m = step(m);
  }
  bool happy = m == 1 || a[m] == 1;
  m = mm;
  while(m != 1 && a[m] == 3) {
    a[m] = happy ? 1 : 2;
    m = step(m);
  }
  return a[mm] == 1;
}

int main() {
  unsigned int a[LEN]; // 0: unknown, 1: happy, 2: unhappy, 3: working.
  for(long i = 2; i < LEN; ++i) {
    a[i] = 0;
  }
  a[1] = 1;

  long A, count;
  std::cin >> count;
  for(int cas = 1; cas <= count; ++cas) {
    std::cin >> A;
    if(happy(A, a)) {
      printf("Case #%d: %li is a Happy number.\n", cas, A);
    }
    else {
      printf("Case #%d: %li is an Unhappy number.\n", cas, A);
    }
  }
  return 0;
}
