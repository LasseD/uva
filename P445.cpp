#include <iostream>

#define LEN 10000

void print(char c, int cnt) {
  for(int i = 0; i < cnt; ++i)
    std::cout << c;
}

int main() {
  char line[LEN];
  int sum = 0;
  while(std::cin.getline(line, LEN)) {
    if(!isprint(line[0])) {
      sum = 0;
      std::cout << std::endl;
      continue;
    }
    char c;
    for(int i = 0; isprint(c = line[i]); ++i) {
      if(c >= '0' && c <= '9')
	sum += c-'0';
      else {
	if(c == '!') {
	  std::cout << std::endl;
	}
	else {
	  print(c == 'b' ? ' ' : c, sum);
	}
	sum = 0;
      }
    }
    std::cout << std::endl;      
  }
  return 0;
}
