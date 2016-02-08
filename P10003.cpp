#include <iostream>

#define MIN(a,b) (((a) < (b)) ? (a) : (b))

// Cuts: 0, p1, p2, ... len
int minCut(int *a, int *cuts, int numCuts) {
  // Base cases:
  if(numCuts == 0)
    return 0;
  if(numCuts == 1)
    return cuts[2];

  // lessCuts = 1:
  for(int i = 0; i < numCuts; ++i)
    a[50+i] = cuts[i+2]-cuts[i];

  // lessCuts = 2+:
  for(int lessCuts = 2; lessCuts <= numCuts; ++lessCuts) {
    // Cut "lessCuts" at position i:
    for(int i = 0; i+lessCuts <= numCuts; ++i) {
      int ai = 50*lessCuts+i;
      a[ai] = 9999999;
      // Try all first cut positions:
      int base = cuts[i+lessCuts+1] - cuts[i];
      for(int firstCut = 0; firstCut < lessCuts; ++firstCut) {
	int tryout = base + a[50*firstCut+i] + a[50*(lessCuts-firstCut-1)+i+firstCut+1];
	a[ai] = MIN(a[ai], tryout);
      }
    }
  }

  /*
  std::cerr << "Number of cuts: " << numCuts << std::endl;
  for(int i = 0; i <= numCuts+1; ++i)
    std::cerr << " " << cuts[i];
  std::cerr << std::endl;
  for(int cuts = 0; cuts <= numCuts; ++cuts) {
    for(int i = 0; i+cuts <= numCuts; ++i) {
      std::cerr << cuts << " cuts from position " << i << " cost: " << a[50*cuts+i] << std::endl;
    }
  }
  std::cerr << "------------------" << std::endl;//*/

  return a[50*numCuts];
}

int main() {
  int a[2550]; // cut len,pos at 50*(len-1)+pos
  for(int i = 0; i < 50; ++i)
    a[i] = 0; // Free to cut first.
  int cuts[52];
  cuts[0] = 0;

  int n, l; // n = |cuts|, l = len.
  while(true) {
    std::cin >> l;
    if(l == 0)
      return 0;
    std::cin >> n;

    for(int i = 1; i <= n; ++i) {
      std::cin >> cuts[i];
    }
    cuts[n+1] = l;
    int cost = minCut(a, cuts, n);
    
    std::cout << "The minimum cutting is " << cost << "." << std::endl;
  }  
}
