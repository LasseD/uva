#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

ul gcd(ul a, ul b) {
  ul c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

ul lcm(ul a, ul b) {
  ul g = gcd(a,b);
  if(g == 0)
    return 0;
  return a/g*b;
}

/*
a <= b: 
GCD(a,b) = G: a%G = b%G = 0 => G|a, G|b
LCM(a,b) = L: L%a = L%b = 0 => a|L, b|L
G|L - else output -1.
a=b=G => OK.

lcm(a,b) = a/gcd(a,b)*b = a/G*b = L => a*b=L*G =>
Choose b = gcd(L,G), a = L*G/b
 */
int main() {
  int T;
  ul G, L;
  std::cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    std::cin >> G >> L;
    if(L%G != 0) {
      std::cout << -1 << std::endl;
      continue;
    }
    ul b = gcd(L,G); // = G
    ul a = L/b*G; // = L because G=b
    if(a > b) // Never happens.
      std::swap(a,b);
    std::cout << a << " " << b << std::endl;
  }
}
