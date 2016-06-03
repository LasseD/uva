#include <iostream>
#include <stdio.h>
#include <algorithm>

typedef std::string str;

int findPermutations(int i, int size, int t, int *perm, int sizePerm, int *a) {
  if(t == 0) {
    // Report and return:
    std::cout << perm[0];
    for(int j = 1; j < sizePerm; ++j)
      std::cout << "+" << perm[j];
    std::cout << std::endl;
    return 1;
  }

  // try all combinations:
  int prev = -1;
  int sum = 0;
  for(int j = i; j < size; ++j) {
    int sub = a[j];
    if(sub != prev && sub <= t) {
      perm[sizePerm] = sub;
      sum += findPermutations(j+1, size, t - sub, perm, sizePerm+1, a);
      prev = sub;
    }
  }
  return sum;
}

int main() {
  int n, t, a[12], perm[12];
  while(true) {
    std::cin >> t >> n;
    if(n == 0)
      return 0;

    for(int i = 0; i < n; ++i)
      std::cin >> a[i];
    std::cout << "Sums of " << t << ":" << std::endl;

    int permutations = findPermutations(0, n, t, perm, 0, a);
    if(permutations == 0)
      std::cout << "NONE" << std::endl;    
  }
}
