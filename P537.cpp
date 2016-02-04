#include <iostream>
#include <stdio.h>

double readDouble(char *w, int &idx) {
  ++idx;
  unsigned long ret = 0;
  char c;
  double neg = (w[idx] == '-') ? -1 : 1;
  if(w[idx] == '-')
    ++idx;
  unsigned long divider = 1;
  bool dot = false;
  for(; isdigit(c = w[idx]) || c == '.'; ++idx) {
    if(c == '.') {
      dot = true;
      continue;
    }
    ret = 10*ret + (c-'0');
    if(dot)
      divider*=10;
  }
  //std::cerr << "Ret: " << ret << ", divider: " << divider << ", c: " << c << std::endl;
  switch(c) {
  case 'm':
    return neg*ret/1000.0/divider;
  case 'k':
    return neg*ret*1000.0/divider;
  case 'M':
    return neg*ret*1000000.0/divider;
  }
  return neg*ret/(double)divider;
}

int main() {
  char c, w[100000];
  // Get cases:
  int cases = 0;
  gets(w);
  int idx = 0;
  for(; isdigit(c = w[idx]); ++idx)
    cases = 10*cases + (c-'0');

  // Handle lines:
  for(int cas = 1; cas <= cases; ++cas) {
    gets(w);
    bool setP = false, setU = false, setI = false;
    double P, U, I;
    idx = 1;
    for(int j = 0; j < 2; ++j) {
      // Find '=':
      for(; w[idx] != '='; ++idx)
	;
      switch(w[idx-1]) {
      case 'P':
	P = readDouble(w, idx);
	setP = true;
	break;
      case 'U':
	U = readDouble(w, idx);
	setU = true;
	break;
      default: //case 'I':
	I = readDouble(w, idx);
	setI = true;
	break;
      }
    }
    printf("Problem #%d\n", cas);
    if(!setP) {
      printf("P=%.2fW\n", U*I);
    }
    else if(!setU) {
      printf("U=%.2fV\n", P/I);
    }
    else if(!setI) {
      printf("I=%.2fA\n", P/U);
    }    
    printf("\n");
  }
}
