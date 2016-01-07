#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

typedef std::pair<int,char> Cnt;

int main() {
  char c, w[1002];
  int counts[129];
  bool first = true;
  while(gets(w)) {
    if(!first)
      std::cout << std::endl;
    first = false;
    for(int i = 32; i <= 128; ++i)
      counts[i] = 0;
    for(int i = 0; (int)(c = w[i]) > 31; ++i) {
      ++counts[(int)c];
    }
    std::vector<Cnt> out;
    for(int i = 32; i <= 128; ++i) {
      if(counts[i] != 0)
	out.push_back(Cnt(counts[i], -i));
    }
    std::sort(out.begin(), out.end());
    for(std::vector<Cnt>::iterator it = out.begin(); it != out.end(); ++it)
      std::cout << -((int)it->second) << " " << it->first << std::endl;
  }
  return 0;
}
