#include <iostream>
#include <stdio.h>
#include <sstream>

typedef unsigned long long ul;

ul gcd(ul a, ul b) {
  ul c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

int main() {
  ul N, M, a[100];
  std::string s;
  std::stringstream ss1;
  std::getline(std::cin,s); ss1 << s; ss1 >> N; 

  for(ul cas = 0; cas < N; ++cas) {
    M = 0;
    std::stringstream ss2;
    std::getline(std::cin,s); ss2 << s; 
    while(ss2 >> a[M])
      ++M;

    ul maxGCD = 1;
    /*
    std::cerr << "DATA:";
    for(ul i = 0; i < M; ++i)
      std::cerr << " " << a[i];
      std::cerr << std::endl;//*/

    for(ul i = 0; i < M; ++i) {
      for(ul j = i+1; j < M; ++j) {
	ul g = gcd(a[i], a[j]);
	if(g > maxGCD)
	  maxGCD = g;
      }
    }
    std::cout << maxGCD << std::endl;
  }
}
