#include <iostream>
#include <string>

#define LEN 10000

int main() {
  std::string s = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./  qwertyuiop  asdfghjkl  zxcvbnm#";
  char c, sub[256];
  for(int i = 1; (c = s[i]) != '#'; ++i) {
    sub[(int)c] = s[i-2];
    if(s[i-2] >= 'A' && s[i-2] <= 'Z')
      sub[(int)c] = s[i-2]-'A'+'a';      
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
