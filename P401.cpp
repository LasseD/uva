#include <iostream>
#include <string>

#define LEN 10000

void buildMirror(char* cMirror) {
  // Setup mirror structure:
  std::string mirrors = "AA E3 HH II JL LJ MM OO S2 TT UU VV WW XX YY Z5 11 2S 3E 5Z 88 ";
  for(unsigned int i = 0; i < mirrors.size(); i+=3) {
    char c1 = mirrors[i];
    char c2 = mirrors[i+1];
    cMirror[(int)c1] = c2;
    cMirror[(int)c2] = c1;
  }
}

bool isPalindrome(const std::string &s) {
  int i = 0;
  int j = (int)s.size()-1;
  for(; i < j; ++i, --j) {
    if(s[i] != s[j])
      return false;
  }
  return true;
}

bool isMirrored(const std::string &s, char* cMirror) {
  int i = 0;
  int j = (int)s.size()-1;
  for(; i <= j; ++i, --j) {
    if(cMirror[(int)s[i]] == 0 || cMirror[(int)s[j]] == 0) {
      return false;
    }
    if(s[i] != cMirror[(int)s[j]])
      return false;
  }
  return true;
}

int main() {
  char cMirror[256];
  for(int i = 0; i < 256; ++i)
    cMirror[i] = 0;
  buildMirror(cMirror);

  // Perform main computation:
  char line[LEN];
  while(std::cin.getline(line, LEN)) {
    int len = 0;
    while(isprint(line[len]))
      ++len;
    line[len] = '\0';
    std::string s(line);
    bool m = isMirrored(s, cMirror);
    bool p = isPalindrome(s);
    
    std::cout << s << " -- is ";
    if(!p && !m)
      std::cout << "not a palindrome." << std::endl << std::endl;
    else if(p && !m)
      std::cout << "a regular palindrome." << std::endl << std::endl;
    else if(!p && m)
      std::cout << "a mirrored string." << std::endl << std::endl;
    else
      std::cout << "a mirrored palindrome." << std::endl << std::endl;
  }
  return 0;
}
