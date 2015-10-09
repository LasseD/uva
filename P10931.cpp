#include <iostream>
#include <string>

int main() {
  long I;
  bool bits[64];
  while(true) {
    // Read and parse input:
    std::cin >> I;
    if(I == 0)
      return 0;
    int numDigits = 1;
    long downI = I;
    while(downI > 1) {
      ++numDigits;
      downI >>= 1;
    }
    int parity = 0;
    for(int i = 0; i < numDigits; ++i) {
      bool bit = (I%2) == 1;
      bits[numDigits-1-i] = bit;
      if(bit)
	++parity;
      I >>= 1;
      //std::cerr << "Reverse bit " << i << " = " << bits[numDigits-1-i] << std::endl;
    }

    // Print:
    std::cout << "The parity of ";
    for(int i = 0; i < numDigits; ++i)
      std::cout << (bits[i] ? "1" : "0");
    std::cout << " is " << parity << " (mod 2)." << std::endl;
  }
}
