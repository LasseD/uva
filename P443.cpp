#include <iostream>
#include <set>

typedef unsigned long long ul;
typedef std::set<ul> set;
#define LEN 5842

void printEnd(ul n) {
  if((n % 100 == 11)||(n % 100 == 12)||(n % 100 == 13)) {
    std::cout << "th";
    return;
  }

  switch(n%10) {
  case 1:
    std::cout << "st";
    break;
  case 2:
    std::cout << "nd";
    break;
  case 3:
    std::cout << "rd";
    break;
  default:
    std::cout << "th";
    break;
  }
}

int main() {
  int multipliers[4] = {2,3,5,7};
  ul a[LEN];
  int idx = 0;
  set s;
  for(int i = 1; i <= 10; ++i)
    s.insert(i);
  while(idx < LEN) {
    ul min = *s.begin();
    s.erase(min);
    a[idx++] = min;
    for(int i = 0; i < 4; ++i) {
      ul mult = multipliers[i]*min;
      if(s.find(mult) == s.end())
	s.insert(mult);
    }
  }

  int N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    std::cout << "The " << N;
    printEnd(N);
    std::cout << " humble number is " << a[N-1] << "." << std::endl;
  }
}
