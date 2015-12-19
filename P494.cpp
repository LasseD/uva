#include <stdio.h>
#include <iostream>

#define LEN 10000

int main() {
  char line[LEN];
  while(std::cin.getline(line, LEN)) {
    int cnt = 0;
    bool inWord = false;
    char c;
    for(int i = 0; isprint(c = line[i]); ++i) {
      if(isalpha(c)) {
	if(!inWord) {
	  ++cnt;
	  inWord = true;
	}
      }
      else {
	inWord = false;
      }
    }
    std::cout << cnt << std::endl;
  }
}
