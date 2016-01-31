#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>

typedef std::string String;
typedef std::pair<int,int> PP;

int main() {
  String w;
  std::getline(std::cin,w);
  int N, M;
  std::stringstream ss2; ss2 << w; ss2 >> N;
  for(int cas = 0; cas < N; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    std::getline(std::cin,w); std::getline(std::cin,w);
    
    // Find length and read indexes:
    std::vector<PP> pp;
    std::vector<String> strings;

    int len = 0;
    std::stringstream ss; ss << w;
    while(ss >> M)
      pp.push_back(PP(M, len++));

    // Read strings:
    std::getline(std::cin,w);
    std::stringstream ss1; ss1 << w;
    String s;
    while(ss1 >> s)
      strings.push_back(s);

    std::sort(pp.begin(), pp.end());
    for(unsigned int i = 0; i < pp.size(); ++i)
      std::cout << strings[pp[i].second] << std::endl;
  }
  return 0;
}
