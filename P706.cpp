#include <iostream>
#include <string>

int main() {
  // Bars of LCD display: top, top-left, top-right, mid, bottom-left, bottom-right, bottom.
  int bars0[7] = {1,1,1,0,1,1,1};
  int bars1[7] = {0,0,1,0,0,1,0};
  int bars2[7] = {1,0,1,1,1,0,1};
  int bars3[7] = {1,0,1,1,0,1,1};
  int bars4[7] = {0,1,1,1,0,1,0};
  int bars5[7] = {1,1,0,1,0,1,1};
  int bars6[7] = {1,1,0,1,1,1,1};
  int bars7[7] = {1,0,1,0,0,1,0};
  int bars8[7] = {1,1,1,1,1,1,1};
  int bars9[7] = {1,1,1,1,0,1,1};
  int *bars[10] = {bars0,bars1,bars2,bars3,bars4,bars5,bars6,bars7,bars8,bars9};

  long s, n;
  int digits[9];
  while(true) {
    // Read and parse input:
    std::cin >> s >> n;
    if(s == 0 && n == 0)
      return 0;
    int numDigits = 1;
    long downN = n;
    while(downN > 9) {
      ++numDigits;
      downN /= 10;
    }
    for(int i = 0; i < numDigits; ++i) {
      digits[numDigits-1-i] = n%10;
      n /= 10;
      //std::cerr << "Reverse digit " << i << " = " << digits[numDigits-1-i] << std::endl;
    }

    // Print top - bars:
    for(int i = 0; i < numDigits; ++i) {
      if(i != 0)
	std::cout << " "; // spacing
      std::cout << " "; // corner
      for(int j = 0; j < s; ++j) // top bar:
	std::cout << (bars[digits[i]][0] ? "-" : " ");
      std::cout << " "; // corner
    }
    std::cout << std::endl;
    // Print the top | bars:
    for(int k = 0; k < s; ++k) {
      for(int i = 0; i < numDigits; ++i) {
	if(i != 0)
	  std::cout << " "; // spacing
	std::cout << (bars[digits[i]][1] ? "|" : " "); // left bar
	for(int j = 0; j < s; ++j) // top bar:
	  std::cout << " ";
	std::cout << (bars[digits[i]][2] ? "|" : " "); // right bar
      }
      std::cout << std::endl;      
    }
    // Print center - bars:
    for(int i = 0; i < numDigits; ++i) {
      if(i != 0)
	std::cout << " "; // spacing
      std::cout << " "; // corner
      for(int j = 0; j < s; ++j) // top bar:
	std::cout << (bars[digits[i]][3] ? "-" : " ");
      std::cout << " "; // corner
    }
    std::cout << std::endl;
    // Print the bottom | bars:
    for(int k = 0; k < s; ++k) {
      for(int i = 0; i < numDigits; ++i) {
	if(i != 0)
	  std::cout << " "; // spacing
	std::cout << (bars[digits[i]][4] ? "|" : " "); // left bar
	for(int j = 0; j < s; ++j) // top bar:
	  std::cout << " ";
	std::cout << (bars[digits[i]][5] ? "|" : " "); // right bar
      }
      std::cout << std::endl;      
    }
    // Print bottom - bars:
    for(int i = 0; i < numDigits; ++i) {
      if(i != 0)
	std::cout << " "; // spacing
      std::cout << " "; // corner
      for(int j = 0; j < s; ++j) // top bar:
	std::cout << (bars[digits[i]][6] ? "-" : " ");
      std::cout << " "; // corner
    }
    std::cout << std::endl;
    // After each case:
    std::cout << std::endl;
  }
}
