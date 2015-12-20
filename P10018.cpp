#include <iostream>

struct Integer {
  unsigned int digits[11];
  int len;
  
  Integer(unsigned long long P) : len(0) {
    while(P > 0) {
      digits[len++] = P%10;
      P/=10;
    }
  }

  bool isPalindrome() {
    for(int i = 0; i < len/2; ++i) {
      if(digits[i] != digits[len-1-i])
	return false;
    }
    return true;
  }

  void print() {
    for(int i = 0; i < len; ++i) {
      std::cout << digits[i];
    }
  }

  void reverseAndAdd() {
    //print(); std::cout << " -> ";
    unsigned int tmp[11];
    for(int i = 0; i < len; ++i)  {
      tmp[i] = digits[i];
      digits[i] = 0;
    }
    digits[len] = 0;
    for(int i = 0; i < len; ++i)  {
      digits[i]+= tmp[i] + tmp[len-1-i];
      if(digits[i] > 9) {
	digits[i+1] += digits[i]/10;
	digits[i] = digits[i]%10;
      }
    }
    if(digits[len] > 0)
      ++len;
    //print(); std::cout << std::endl;
  }
};

int main() {
  int N;
  std::cin >> N;
  for(int ignore = 0; ignore < N; ++ignore) {
    unsigned long long P;
    std::cin >> P;
    int iterations = 0;
    Integer i(P);
    while(!i.isPalindrome()) {
      ++iterations;
      i.reverseAndAdd();
    }    
    std::cout << iterations << " ";
    i.print();
    std::cout << std::endl;
  }  
}
