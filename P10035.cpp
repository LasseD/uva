#include <iostream>
#include <stdio.h>

/*
Count carries
 */
int main() {
  while(true) {
    // Read input and check stop condition:
    unsigned long a, b;
    std::cin >> a >> b;
    if(a == 0 && b == 0)
      return 0;

    // Compute output:
    int carries = 0;
    bool lastCarry = false;
    while(a > 0 || b > 0) {
      int ra = a%10;
      int rb = b%10;
      bool carry = lastCarry ? ra+rb >= 9 : ra+rb >= 10;
      if(carry)
	++carries;
      lastCarry = carry;
      a/=10;
      b/=10;
    }

    // Pretty print output:
    if(carries == 0)
      printf("No carry operation.\n");
    else if(carries == 1)
      printf("1 carry operation.\n");
    else
      printf("%i carry operations.\n", carries);
  }
}
