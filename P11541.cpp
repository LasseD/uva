#include <iostream>
#include <stdio.h>

typedef   std::string String;

void decodeAndPrint(String s) {
  unsigned int i = 0;
  char c;
  while(i < s.length() && 'A' <= (c = s[i++]) && 'Z' >= c) {
    char toCopy = c;
    int counter = 0;
    while(isdigit(c = s[i])) {
      counter = 10*counter + (c-'0');
      ++i;
    }
    for(int j = 0; j < counter; ++j)
      std::cout << toCopy;
  }
}

int main() {
  int cases;
  String s;
  std::cin >> cases;
  for(int cas = 1; cas <= cases; ++cas) {
    std::cin >> s;
    std::cout << "Case " << cas << ": ";
    decodeAndPrint(s);
    std::cout << std::endl;
  }
}
