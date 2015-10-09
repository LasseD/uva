#include <iostream>
#include <ctype.h>

int main() {
  char w[100];
  while(std::cin.getline(w, 100)) {
    // Read and parse input:
    int n = 0;
    for(int i = 0; isprint(w[i]); ++i) {
      if(w[i] >= '0' && w[i] <= '9')
	n = 10*n + (w[i]-'0');
    }
    std::cerr << " Running for " << n << std::endl;

    // Compute:
    int numEmpty = n;
    int numFull = 0;
    int numDrinked = n;
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
