#include <stdio.h>
#include <iostream>

typedef std::string String;

bool isVowel(char c) {
  switch(c) {
  case 'a':
  case 'e':
  case 'i':
  case 'o':
  case 'u':
    return true;
  default:
    return false;
  }
}

int main() {
  int N;
  String a, b;
  std::cin >> N;
  for(int cas = 0; cas < N; ++cas) {
    std::cin >> a >> b;
    if(a.size() != b.size()) {
      std::cout << "No" << std::endl;
    }
    else {
      bool ok = true;
      for(unsigned int i = 0; ok && i < a.size(); ++i) {
	char c1 = a[i];
	char c2 = b[i];
	if(isVowel(c1) && isVowel(c2))
	   continue;
	ok = c1 == c2;
      }
      if(ok)
	std::cout << "Yes" << std::endl;
      else
	std::cout << "No" << std::endl;
    }
  }
  return 0;
}
