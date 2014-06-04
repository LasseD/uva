#include <iostream>
#include <stdio.h>

bool checkTree(int test, int &leaf) {
  leaf = false;
  // Read (:
  int M;
  while((M = fgetc(stdin)) != '(') {
  }
  // Read M or ):
  while(!(isdigit(M = fgetc(stdin)) || M == ')' || M == '-')) {
  }
  if(M == ')') {
    //    std::cerr << "()";
    leaf = true;
    return false;
  }

  ungetc(M, stdin);
  int read = fscanf(stdin, "%i", &M);
    
  //  std::cerr << "[" << M << " ";

  // Read sub trees:
  int leafL;
  int leafR;
  bool res = checkTree(test-M, leafL);
  res |= checkTree(test-M, leafR);
  res = leafL && leafR && test==M || res;

  // Read ):
  while((M = fgetc(stdin)) != ')')
    ;
  //  std::cerr << " ]";
  return res;
}

int main() {
  while(true) {
    // Read N:
    int N;
    int read = fscanf(stdin, "%i", &N);
    // Exit if done.
    if(read != 1)
      return 0;
    //std::cerr << "TEST: " << N << std::endl;
    
    // Read tree:
    int ignore;
    if(checkTree(N, ignore)) {
      std::cout << "yes" << std::endl;
    }
    else {
      std::cout << "no" << std::endl;
    }
  }  
}
