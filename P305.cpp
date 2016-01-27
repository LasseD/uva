#include <stdio.h>
#include <iostream>

/*
1: 01 m=2
2: 0011 m=7 => 00X0 -> 00XX
3: 000111 m=5 OK
4: OK
 */
void advanceOne(bool const * const set, int n, int &idx) {
  do {
    ++idx;
    if(idx == n)
      idx = 0;
  }
  while(set[idx]);
}

void advanceM(bool const * const set, int n, int m, int &idx) {
  for(int i = 0; i < m; ++i)
    advanceOne(set, n, idx);
}

bool solves(int k, int m, bool * const set) {
  int n = 2*k;
  int idx = (m-1)%n;
  if(idx < k)
    return false;
  for(int i = k; i < n; ++i)
    set[i] = false;
  for(int i = 1; i < k; ++i) {
    set[idx] = true;
    advanceM(set, n, m, idx);
    if(idx < k)
      return false;
  }
  return true;
}

int computeM(int k) {
  bool set[26];
  for(int i = 0; i < k; ++i)
    set[i] = false;

  for(int i = k+1; i > 0; ++i) {
    if(solves(k, i, set))
      return i;
  }
  return -1;  
}

int main() {
  int a[13] = {2,7,5,30,169,441,1872,7632,1740,93313,459901,1358657,2504881};

  int k;
  while(true) {
    std::cin >> k;
    if(k == 0)
      return 0;
    std::cout << a[k-1] << std::endl;
    //std::cout << computeM(k) << std::endl;
    /*
    bool set[26];
    for(int i = 0; i < k; ++i)
      set[i] = false;
    std::cerr << solves(k, a[k-1], set) << std::endl;*/
  }
}
