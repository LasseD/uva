#include <iostream>
#include <stdio.h>
#include <map>
#include <set>
#include <stack>
#include <algorithm>

void encode(char c, char *encoded) {
  int idx = (int)(4*c);
  if(c < 100) {
    encoded[idx] = (char)('0'+(c%10));
    encoded[idx+1] = (char)('0'+(c/10));
    encoded[idx+2] = '\0';
  }
  else {
    encoded[idx] = (char)('0'+(c%10));
    encoded[idx+1] = (char)('0'+((c/10)%10));
    encoded[idx+2] = (char)('0'+(c/100));
    encoded[idx+3] = '\0';
  }
}

void decode(char *w, const std::set<char> &legal) {
  char c1, c2, c3;
  int i = 0;

  while(isdigit(c1 = w[i]) && isdigit(c2 = w[++i])) {
    int a = 10*(c1-'0') + (c2-'0');
    if(legal.find((char)a) != legal.end()) {
      std::cout << ((char)a);
      ++i;
      continue;
    }
    c3 = w[++i];
    a = 100*(c1-'0') + 10*(c2-'0') + (c3-'0');
    std::cout << ((char)a);
    ++i;
  }
  std::cout << std::endl;
}

int main() {
  char c, line[300], encoded[5000]; // encoded: c -> [4c; 4c+4]
  std::set<char> legal;

  for(c = 'A'; c <= 'Z'; ++c) {
    encode(c, encoded);
    legal.insert(c);
  }
  for(c = 'a'; c <= 'z'; ++c) {
    encode(c, encoded);
    legal.insert(c);
  }
  std::string special = " !,.;:?";
  for(int i = 0; i < 7; ++i) {
    c = special[i];
    encode(c, encoded);
    legal.insert(c);
  }
  
  while(gets(line)) {
    int len = 0;
    while(isprint(line[len]))
      ++len;
    std::reverse(line, line+len);

    if(isdigit(line[0])) {
      // Digits to chars:
      decode(line, legal);
    }
    else {
      // encode chars:
      for(int i = 0; isprint(c = line[i]); ++i)
	std::cout << (&encoded[4*(int)c]);
      std::cout << std::endl;
    }
  }
  return 0;
}
