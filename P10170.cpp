#include <iostream>
#include <stdio.h>

typedef unsigned long long ul;

ul daysUsedBy(ul group, ul S) {
  return ((2*S+group)*(group+1))/2;
}

// S = initial group size staying for S days.
// D = Day where group size is measured.
ul groupAtDay(ul S, ul D) {
  if(D <= S)
    return S;
  ul s = S; // Smaller than the group at the hotel at day D.
  ul h = S+D; // Larger than or equal to group at day D.
  while(s < h-1) {
    ul mid = (s+h)/2;
    //std::cerr << "Search day " << D << ", low=" << s << ", high=" << h << ", mid=" << mid << ", days for mid=" << daysUsedBy(mid-S, S) << std::endl;
    if(daysUsedBy(mid-S, S) < D) {
      s = mid;
    }
    else {
      h = mid;
    }
  }
  return h;
}

int main() {
  ul S, D;
  while(std::cin >> S >> D) {
    std::cout << groupAtDay(S, D) << std::endl;
  }
  return 0;
}
