#include <iostream>
#include <stdio.h>
#include <stack>
#include <string>
#include <sstream>

typedef std::string String;
typedef std::stack<String> Stack;
typedef std::stringstream SS;

bool isNormalLetter(char c) {
  return c != '[' && c != ']' && isprint(c);
}

int main() {
  String input;
  char c;

  while(std::cin >> input) {
    Stack s;
    SS ss;    
    
    unsigned int j = 0;
    while(j < input.size() && isprint(c = input[j++])) {
      if(c == '[') {
	unsigned int k = j;
	while(isNormalLetter(c = input[k]))
	  ++k;
	if(k == j)
	  continue;
	input[k] = '\0';
	s.push(String(&input[j]));
	input[k] = c;
	j = k;
      }
      else if(c == ']') {
        // nop
      }
      else {
	ss << c;
      }
    }

    // First print Stack, then SS.
    while(!s.empty()) {
      std::cout << s.top();
      s.pop();
    }
    std::cout << ss.str() << std::endl;
  }
}
