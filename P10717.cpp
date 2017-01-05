#include <iostream>
#include <stdio.h>

using namespace std;

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

ul lcm(ul a, ul b) {
  ul g = gcd(a,b);
  return a*b/g;
}

int main() {
  int n, t;
  ul table, coins[50];
  while(true) {
    // Read case:
    cin >> n >> t;
    if(n == 0 && t == 0)
      return 0;
    for(int i = 0; i < n; ++i)
      cin >> coins[i];
    
    for(int i = 0; i < t; ++i) {
      cin >> table;
      ul bestLarger = 1000000000000;
      ul bestSmaller = 0;

      for(int c0 = 0; c0 < n; ++c0) {
	for(int c1 = c0+1; c1 < n; ++c1) {
	  ul lcm1 = lcm(coins[c1], coins[c0]);
	  for(int c2 = c1+1; c2 < n; ++c2) {
	    ul lcm2 = lcm(coins[c2], lcm1);
	    for(int c3 = c2+1; c3 < n; ++c3) {
	      ul lcm3 = lcm(coins[c3], lcm2);
	      //cerr << lcm1 << " " << lcm2 << " " << lcm3  << ", table=" << table << endl;

	      ul larger = ((table+lcm3-1) / lcm3) * lcm3;
	      if(larger < bestLarger)
		bestLarger = larger;

	      ul smaller = (table / lcm3) * lcm3;
	      if(smaller > bestSmaller)
		bestSmaller = smaller;
	    }
	  }
	}
      }
      cout << bestSmaller << " " << bestLarger << endl;
    }
  }
}
