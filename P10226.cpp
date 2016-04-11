#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

typedef std::map<std::string,unsigned int> Map;

int main() {
  char c, w[39];
  gets(w);
  int N = 0;
  for(int i = 0; isdigit(c = w[i]); ++i)
    N = 10*N + (c-'0');
  gets(w);
  for(int cas = 0; cas < N; ++cas) {
    if(cas != 0)
      printf("\n");
    Map map;
    unsigned int sum = 0;
    while(gets(w)) {
      /*for(int i = 0; (c = w[i]) != '\0'; ++i) {
	if(c == '\r' || c == '\n')
	  w[i] = '\0';
	  }*/ // For Windows.
      std::string s(w);
      if(s.size() == 0)
	break;
      Map::iterator it = map.find(s);
      ++sum;
      if(it == map.end())
	map.insert(std::make_pair(s,1));
      else {
	unsigned int j = it->second;
	map.erase(it);
	map.insert(std::make_pair(s,j+1));
      }
    }
    // Print:
    for(Map::const_iterator it = map.begin(); it != map.end(); ++it)
      printf("%s %.4f\n", it->first.c_str(), it->second*100/(double)sum);
  }
}
