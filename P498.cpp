#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <sstream>

typedef std::string String;
typedef std::stringstream SS;
typedef std::vector<int> Vector;

long long eval(Vector &c, long long x) {
  long long ret = 0;
  long long xn = 1;
  for(int i = (int)c.size()-1; i >= 0; --i, xn*=x)
    ret += c[i]*xn;
  return ret;
}

int main() {
  String w;
  int a;
  
  while(std::getline(std::cin,w)) {
    SS ss1, ss2;
    ss1 << w;
    
    Vector c;
    while(ss1 >> a)
      c.push_back(a);
    std::getline(std::cin,w);
    ss2 << w;
    bool first = true;
    while(ss2 >> a) {
      if(!first)
	std::cout << " ";
      first = false;
      std::cout << eval(c, a);
    }
    std::cout << std::endl;
  }  
}
