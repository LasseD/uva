#include <iostream>
#include <string>

int main() {
  int n;
  while(true) {
    // Read and parse input:
    std::cin >> n;
    if(n == 0)
      return 0;
    std::cerr << " Running for " << n << std::endl;

    // Compute:
    int numEmpty = n;
    int numFull = 0;
    int numDrinked = 0;
    while(numEmpty >= 2) {
      if(numEmpty > 2) {
	int newFull = numEmpty/3;
	numEmpty -= newFull*3;
	numFull += newFull;
      }
      else { // borrow one:
	++numDrinked;
	break;
      }
      numDrinked += numFull;
      numEmpty += numFull;
      numFull = 0;
    }

    // Print:
    std::cout << numDrinked << std::endl;
  }
}
