#include <stdio.h>
#include <iostream>
#include <stack>

typedef std::stack<char> Stack;
typedef unsigned long long ul;

int main() {
  ul in, from, to;
  while(std::cin >> from >> to >> std::hex >> in >> std::dec) {
    std::cout << std::hex << std::uppercase << in << std::nouppercase << std::dec;
    ul inAsDec = 0;
    ul multiplier = 1;
    bool ok = true;
    while(in > 0) {
      ul digit = in & 0x0F;
      if(digit >= from) {
	ok = false;
	std::cout << " is an illegal base " << from << " number" << std::endl;
	break;
      }
      inAsDec += digit*multiplier;
      multiplier*=from;
      in >>= 4;
    }
    if(!ok)
      continue;
      
    //std::cerr << "In as decimal: " << inAsDec << std::endl;
    Stack s;
    if(inAsDec == 0)
      s.push('0');
    while(inAsDec > 0) {
      ul digit = inAsDec % to;
      if(digit > 9)
	s.push('A' + digit-10);
      else
	s.push('0' + digit);
      inAsDec /= to;
    }
    std::cout << " base " << from << " = ";
    while(!s.empty()) {
      std::cout << s.top();
      s.pop();
    }
    std::cout << " base " << to << std::endl;
  }
  return 0;
}
