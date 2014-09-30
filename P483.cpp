#include <iostream>

#define SIZE 3000

int main() {
  char line[SIZE];
  while(std::cin.getline(line, SIZE)) {
    int begin = 0;
    while(true) {
      // spool:
      while(line[begin] == ' ' || line[begin] == '\t') {
	++begin;
      }
      int end = begin+1;
      while(!(line[end] == ' ' || line[end] == '\t' || line[end] == '\r' || line[end] == '\n' || line[end] == '\0')) {
	++end;
      }
      for(int i = 0; begin+i < end-i-1; ++i) {
	std::swap(line[begin+i], line[end-i-1]);
      }
      if(line[end] == '\n' || line[end] == '\r' || line[end] == '\0') {
	line[end] = '\0';
	break;
      }
      begin = end+1;
    }
    std::cout << line << std::endl;
  }
  return 0;
}
