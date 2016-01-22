#include <iostream>
#include <stdio.h>
#include <map>

typedef std::map<std::string,int> map;

void addAll(char *w, int i, int len, map &m, int &idx) {
  if(i == len) {
    m.insert(std::make_pair(std::string(w), idx++));
    return;
  }
  for(char c = (i == 0 ? 'a' : ((char)w[i-1]+1)); c <= 'z'; ++c) {
    w[i] = c;
    addAll(w, i+1, len, m, idx);
  }
}

int main() {
  map m;
  int idx = 1;
  for(int len = 1; len <= 5; ++len) {
    char w[6];
    w[len] = '\0';
    addAll(w, 0, len, m, idx);
  }

  std::string s;
  while(std::cin >> s) {
    map::const_iterator it = m.find(s);
    if(it == m.end()) {
	std::cout << "0" << std::endl;
    }
    else {
      std::cout << it->second << std::endl;
    }
  }
  return 0;
}
