#include <iostream>
#include <stdio.h>
#include <cstring>

int main() {
  int N, counts[26];
  char c, w[1009];
  scanf("%d\n", &N);
  for(int cas = 0; cas < N; ++cas) {
    gets(w);
    memset(counts, 0, 26*sizeof(int));
    int max = 0;
    for(int i = 0; isprint(c = w[i]); ++i) {
      if(c >= 'a' && c <= 'z') {
	++counts[c-'a'];
	if(counts[c-'a'] > max)
	  max = counts[c-'a'];
      }
      else if(c >= 'A' && c <= 'Z') {
	++counts[c-'A'];
	if(counts[c-'A'] > max)
	  max = counts[c-'A'];
      }
    }
    for(int i = 0; i < 26; ++i) {
      if(counts[i] == max)
	std::cout << (char)('a'+i);
    }
    std::cout << std::endl;
  }
  return 0;
}
