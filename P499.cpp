#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

typedef std::pair<int,char> pp;

int main() {
  int cnts[256];
  char c, s[10000];
  while(gets(s)) {
    // Reset:
    for(char i = 'A'; i <= 'z'; ++i)
      cnts[(int)i] = 0;
    // Count:
    for(int i = 0; (c = s[i]) != '\0'; ++i) {
      if(isalpha(c))
	cnts[(int)c]++;
    }
    std::vector<pp> v;
    for(char i = 'A'; i <= 'z'; ++i)
      v.push_back(pp(-cnts[(int)i],i));
    std::sort(v.begin(), v.end());
    for(int i = 0; v[i].first == v[0].first; ++i)
      std::cout << v[i].second;
    std::cout << " " << -v[0].first << std::endl;
  }
}
