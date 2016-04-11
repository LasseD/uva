#include <stdio.h>
#include <iostream>

int main() {
  unsigned long in, from, to;
  char out[8];
  out[7] = '\0';
  while(std::cin >> std::hex >> in >> std::dec >> from >> to) {
    unsigned int inAsDec = 0;
    unsigned int multiplier = 1;
    while(in > 0) {
      unsigned int digit = in & 0x0F;
      inAsDec += digit*multiplier;
      multiplier*=from;
      in >>= 4;
    }
    if(inAsDec == 0) {
      printf("      0\n");
      continue;
    }
      
    //std::cerr << "In as decimal: " << inAsDec << std::endl;
    for(int i = 0; i < 7; ++i)
      out[i] = ' ';
    int j = 6;
    bool done = false;
    while(inAsDec > 0) {
      if(j < 0) {
	printf("  ERROR\n");
	done = true;
	break;
      }
      unsigned int digit = inAsDec % to;
      if(digit > 9)
	out[j--] = 'A' + digit-10;
      else
	out[j--] = '0' + digit;
      inAsDec /= to;
    }
    if(!done) {
      printf("%s\n", out);
    }
  }
  return 0;
}
