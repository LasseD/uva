#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

ul gcd(ul a, ul b) {
  ul c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

ul readBinaryLine() {
  char w[39];
  gets(w);

  ul ret = 0;
  for(int i = 0; w[i] == '0' || w[i] == '1'; ++i) {
    ret = (ret<<1)+(w[i]=='1'?1:0);
  }
  return ret;
}

ul readDecimalLine() {
  char w[39];
  gets(w);

  ul ret = 0;
  for(int i = 0; isdigit(w[i]); ++i) {
    ret = (ret*10)+(w[i]-'0');
  }
  return ret;
}

int main() {
  ul cases = readDecimalLine();
  for(ul cas = 1; cas <= cases; ++cas) {
    std::cout << "Pair #" << cas << ": ";
    ul cd = gcd(readBinaryLine(), readBinaryLine());
    if(cd != 1)
      std::cout << "All you need is love!" << std::endl;
    else
      std::cout << "Love is not all you need!" << std::endl;
  }
}
