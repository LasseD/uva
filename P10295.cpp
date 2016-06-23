#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <sstream>
#include <map>

typedef std::string String;
typedef std::stringstream SS;
typedef std::map<String,int> Map;

void die() {
  int* d = NULL;
  d[0] = 666;
}

int main() {
  int m, n, pay;
  Map map;

  String s;
  std::stringstream ss1;
  std::getline(std::cin,s); ss1 << s; ss1 >> m >> n;

  for(int i = 0; i < m; ++i) {
    std::stringstream ss2;
    std::getline(std::cin,s); ss2 << s; ss2 >> s >> pay;
    if(map.find(s) != map.end())
      die();
    map.insert(std::make_pair(s, pay));
  }

  for(int i = 0; i < n; ++i) {
    bool done = false;
    long sum = 0;
    while(!done) {
      std::stringstream ss2;
      std::getline(std::cin,s); ss2 << s; 
      while(ss2 >> s) {
	if(s[0] == '.') {
	  done = true;
	  break;
	}
	if(map.find(s) != map.end())
	  sum += map[s];
      }
    }    
    std::cout << sum << std::endl;
  }
  return 0;
}
