#include <iostream>
#include <string>

#define LEN 10000

int main() {
  std::string s = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./x";
  char c, sub[256];
  for(int i = 1; (c = s[i]) != 'x'; ++i) {
    sub[(int)c] = s[i-1];
  }

  char line[LEN];
  while(std::cin.getline(line, LEN)) {
    for(int i = 0; isprint(c = line[i]); ++i) {
      if(c == ' ')
	std::cout << ' ';
      else
	std::cout << sub[(int)c];
    }
    std::cout << std::endl;    
  }
  return 0;
}
