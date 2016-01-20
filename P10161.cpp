#include <iostream>
#include <cmath>

typedef unsigned long ul;

int main() {
  ul N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    ul root = (ul)sqrt(N-0.5);
    ul square = root*root;
    ul remainder = N-square;
    ul nextSide = root+1;
    //std::cerr << N << ": " << std::endl << "root: " << root << ", square: " << square << ", remainder: " << remainder << ", nextSide: " << nextSide << std::endl;
    if(root % 2 == 1) {
      if(remainder > nextSide) {
	std::cout << nextSide << " " << (2*nextSide-remainder) << std::endl; 
      }
      else {
	std::cout << remainder << " " << nextSide << std::endl; 
      }
    }
    else {
      if(remainder > nextSide) {
	std::cout << (2*nextSide-remainder) << " " << nextSide << std::endl; 
      }
      else {
	std::cout << nextSide << " " << remainder << std::endl; 
      }
    }
  }
}
