#include <iostream>
#include <stdio.h>

int main() {
  int N;
  std::cin >> N;
  char w1[201], w2[201];
  for(int cas = 0; cas < N; ++cas) {
    std::cin >> w1 >> w2;
    int i = 0;
    int j = 0;
    int carry = 0;
    bool first = true;
    while(isprint(w1[i]) || isprint(w2[j])) {
      int sum = carry;
      if(isprint(w1[i]))
	sum += w1[i++]-'0';
      if(isprint(w2[j]))
	sum += w2[j++]-'0';
      if(!first || (sum%10!=0)) {
	std::cout << (sum%10);
	first = false;
      }
      carry = sum/10;
    }
    if(carry != 0)
      std::cout << carry;
    std::cout << std::endl;
  }
  return 0;  
}
