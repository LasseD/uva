#include <stdio.h>
#include <iostream>
#include <set>

typedef unsigned long long ll;

/*
Assume
a < b, x > y:
a^x = b^y =>
a^x = b^x * b^(y-x) =>
(a/b)^x = b^(y-x) => b|a
 */
int log2(ll i) {
  int res = 0;
  while(i != 0) {
    i>>=1;
    ++res;
  }
  return res;
}

int main() {
  ll llMax = 0;
  --llMax;
  const ll lMax =          0xFFFFFFFF;

  std::set<ll> sp;
  sp.insert(1);

  for(ll base = 2; base <= 0xFFFF; ++base) {
    for(ll base2 = base*base; base2 <= lMax; base2*=base) {
      for(ll base3 = base2*base2; true; base3*=base2) {
	sp.insert(base3);
	if(base3 > llMax/base2)
	  break;
      }
    }
  }

  for(std::set<ll>::const_iterator it = sp.begin(); it != sp.end(); ++it) {
    std::cout << *it << std::endl;
  }//*/ 
  return 0;
}
