#include <iostream>
#include <map>
#include <set>
#include <algorithm>

void flip(int * a, int pos) {
  /*for(int i = 0; i < 5; ++i) {
    std::cerr << a[i] << " ";
  }
  std::cerr << "->" << std::endl;//*/

  int flips = (pos+1)/2;
  for(int i = 0; i < flips; ++i) {
    std::swap(a[i],a[pos-i]);
  }

  /*for(int i = 0; i < 5; ++i) {
    std::cerr << a[i] << " ";
  }
  std::cerr << std::endl;//*/
}

int main() {
  char line[30*3+2];
  while(std::cin.getline(line,30*3+2)) {
    // Read pancakes:    
    int pancakes[30];
    int pancakesSorted[30];
    int n = 0;    
    int pancake = 0;
    for(int i = 0; i < 92; ++i) {
      char c = line[i];
      if(c >= '0' && c <= '9') {
	pancake = 10*pancake + (c-'0');
      }
      else {
	if(pancake != 0) {
	  pancakesSorted[n] = pancake;
	  pancakes[n++] = pancake;
	  pancake = 0;
	}
	if(c != ' ') {
	  break;
	}
      }
    }
    if(n == 0)
      continue;
    // sort pancakes:
    std::sort(pancakesSorted, &(pancakesSorted[n]));
    //std::reverse(pancakesSorted, &(pancakesSorted[n]));
    std::cout << line << std::endl;

    // Run pancakes:
    for(int i = n-1; i >= 0; --i) {
      int sizeToFind = pancakesSorted[i];
      int j = i;
      while(pancakes[j] != sizeToFind)
	--j;

      if(j == i) {
	//std::cerr << "Pan " << sizeToFind << " is already at pos. " << i << std::endl;
	continue; // OK: no flip.
      }
      if(j != 0) { // Need to end flip:
	//std::cerr << "Flipping " << sizeToFind << " from " << j << " to end" << std::endl;
	flip(pancakes, j);
	std::cout << (n-j) << " ";
      }
      else {
	//std::cerr << "End " << sizeToFind << " at end!" << std::endl;
      }
      //std::cerr << "Flipping " << sizeToFind << " from end to " << i << std::endl;

      flip(pancakes, i);
      std::cout << (n-i) << " ";
	
      //std::cerr << sizeToFind << " ";
    }
    //std::cerr << std::endl;
    std::cout << "0" << std::endl;
    
  }
  return 0;
}
