#include <iostream>
#include <stdio.h>

// result = a*A+b*B = c*A+d*B
long gcd(long A, long B, long &a, long &b, long &c, long &d) {
  while(A != B) {
    if(A > B) {
      long multiplesOfBToSubtract = A%B == 0 ? A/B-1 : A/B;
      A -= multiplesOfBToSubtract*B;
      a -= multiplesOfBToSubtract*c;
      b -= multiplesOfBToSubtract*d;
    }
    else { // B > A:
      long multiplesOfAToSubtract = B%A == 0 ? B/A-1 : B/A;
      B -= multiplesOfAToSubtract*A;
      c -= multiplesOfAToSubtract*a;
      d -= multiplesOfAToSubtract*b;
    }
  }
  return A;
}

long abs(long a) {
  if(a < 0)
    return -a;
  return a;
}

bool firstIsBest(long a, long b, long c, long d) {
  long sumNum1 = abs(a)+abs(b);
  long sumNum2 = abs(c)+abs(d);
  if(sumNum1 < sumNum2)
    return true;
  if(sumNum1 > sumNum2)
    return false;
  return a < b;
}

int main() {
  long A, B;
  while(std::cin >> A >> B) {
    long a = 1;
    long b = 0;
    long c = 0;
    long d = 1;
    long D = gcd(A, B, a, b, c, d);
    //std::cerr << "gcd(" << A << "," << B << ") = " << D << " = " << a << "*" << A << "+" << b << "*" << B << " = " << c << "*" << A << "+" << d << "*" << B << std::endl;
    if(firstIsBest(a, b, c, d))
      std::cout << a << " " << b << " " << D << std::endl;
    else
      std::cout << c << " " << d << " " << D << std::endl;
  }
  return 0;
}
