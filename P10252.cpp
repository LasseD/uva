#include <iostream>
#include <stdio.h>

#define MIN(a,b) ((a)<(b) ? (a) : (b))

int main() {
  char c, s1[1009], s2[1009];
  unsigned int counts1[26], counts2[26];
  while(gets(s1) && gets(s2)) {
    // Reset counters:
    for(int i = 0; i < 26; ++i) {
      counts1[i] = counts2[i] = 0;
    }
    // Count for s1 and s2:
    for(int i = 0; isprint(c = s1[i]); ++i)
      ++counts1[c-'a'];
    for(int i = 0; isprint(c = s2[i]); ++i)
      ++counts2[c-'a'];
    for(int i = 0; i < 26; ++i) {
      int cnt = MIN(counts1[i], counts2[i]);
      if(cnt == 0)
	continue;
      for(int j = 0; j < cnt; ++j)
	std::cout << (char)('a'+i);
    }
    std::cout << std::endl;
  }
  return 0;
}
