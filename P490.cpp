#include <iostream>
#include <stack>

#define MAX_SIZE 101

int main() {
  // read:
  std::stack<std::string> stack;
  char line[MAX_SIZE+2];
  while(std::cin.getline(line, MAX_SIZE+2)) {
    for(int i = 0; i < MAX_SIZE+2; ++i) {
      if(line[i] == '\r' || line[i] == '\n')
	line[i] = '\0';
    }
    stack.push(std::string(line));
  }
  
  char *m = new char[MAX_SIZE*MAX_SIZE];
  for(int i = 0; i < MAX_SIZE*MAX_SIZE; ++i)
    m[i] = '\0';
  // save:
  int lineI = 0;
  while(!stack.empty()) {
    std::string l = stack.top();
    stack.pop();
    for(unsigned int i = 0; i < l.size(); ++i) {
      m[MAX_SIZE*i+lineI] = l[i];
      int prevLineI = lineI-1;
      while(prevLineI >= 0 && m[MAX_SIZE*i+prevLineI] == '\0') {
	m[MAX_SIZE*i+prevLineI] = ' ';
	--prevLineI;
      }
    }
    ++lineI;
  }

  // write:
  for(int i = 0; i < MAX_SIZE; ++i) {
    if(m[MAX_SIZE*i] == '\0')
      break;
    std::cout << &m[MAX_SIZE*i] << std::endl;
  }
  delete[] m;
  return 0;
}
