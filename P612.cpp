#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string.h>

typedef std::pair<int,int> Rank;

int sortedness(char* w, int n) {
  char copy[109];
  memcpy(copy, w, n+1);

  char letters[4] = {'A','C','G','T'};
  int ret = 0;
  for(int i = 0; i < 3; ++i) {
    char letter = letters[i];

    int toAdd = 0;
    char c;
    for(int j = 0; (c = copy[j]) >= letter; ++j) {
      if(c == letter) {
	ret += toAdd;
      }
      else {
	copy[toAdd] = c;
	if(j > toAdd)
	  copy[j] = letter;
	++toAdd;
      }
    }
    //std::cerr << "After " << letter << ": toAdd=" << toAdd << ", ret=" << ret << ", copy=" << copy << std::endl;
  }
  return ret;
}

int main() {
  int M, n, m;
  char w[109];
  std::cin >> M;
  for(int cas = 0; cas < M; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    std::vector<std::pair<Rank,std::string> > v;

    std::cin >> n >> m;
    for(int i = 0; i < m; ++i) {
      std::cin >> w;
      w[n] = '\0';
      std::string s(w);
      //std::cerr << i << ": " << s << std::endl;
      v.push_back(std::make_pair(Rank(sortedness(w, n),i), s));
    }

    std::sort(v.begin(), v.end());
    for(int i = 0; i < m; ++i) {
      std::cout << v[i].second << std::endl;
    }
  }
}
