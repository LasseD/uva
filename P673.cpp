#include <iostream>
#include <ctype.h>
#include <stack>

bool ok(char *w) {
  std::stack<char> s;
  char c;
  for(int i = 0; isprint((c = w[i])); ++i) {
    if(c == '[' || c == '(')
      s.push(c);
    else {
      if(s.empty())
	return false;
      if(c == ')') {
	if(s.top() != '(')
	  return false;
      }
      else {
	if(s.top() != '[')
	  return false;
      }
      s.pop();
    }
  }
  return s.empty();
}

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  std::cin.getline(w, 20);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return ret;
}

int main() {
  char w[200];
  unsigned int n = readUInt();
  for(unsigned int i = 0; i < n; ++i) {
    std::cin.getline(w, 200);
    if(ok(w))
      std::cout << "Yes" << std::endl;
    else
      std::cout << "No" << std::endl;
  }
}
