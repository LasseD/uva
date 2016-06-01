#include <iostream>
#include <stdio.h>

int main() {
  char c, w1[109], w2[109];
  // Parse n:
  int n = 0;
  gets(w1);
  for(int i = 0; isdigit(c = w1[i]); ++i)
    n = 10*n + (c-'0');  

  for(int cas = 0; cas < n; ++cas) {
    gets(w1);
    gets(w2);

    // Parse first line:
    int idxSeparators[4];
    int separatorCounter = 0;
    int len1;
    for(len1 = 0; isprint(c = w1[len1]); ++len1) {
      if(c == '>' || c == '<') {
	idxSeparators[separatorCounter++] = len1+1;
	w1[len1] = '\0';
	//std::cerr << "Found separator " << c << " at position " << len1 << std::endl;
      }
    }
    w1[len1] = '\0';
    
    // Parse second line:
    int idxEllipsis;
    for(idxEllipsis = 0; (c = w2[idxEllipsis]) != '.'; ++idxEllipsis)
      ;
    w2[idxEllipsis] = '\0';
    
    // Output c1:
    std::cout << w1;
    for(int i = 0; i < 4; ++i)
      std::cout << &w1[idxSeparators[i]];
    std::cout << std::endl;
    
    // output c2: w2 s4s3s2s5
    std::cout << w2 << &w1[idxSeparators[2]] << &w1[idxSeparators[1]] << &w1[idxSeparators[0]] << &w1[idxSeparators[3]] << std::endl;
  }
}
