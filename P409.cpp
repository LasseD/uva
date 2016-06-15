#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <set>

typedef std::string String;
typedef std::set<String> Set;
typedef std::stringstream SS;
typedef std::pair<int,std::string> Excuse;

bool notIsAlpha(char c) {
  return !isalpha(c);
}

int badness(const String &excuse, Set keywords, int K) {
  int ret = 0;
  
  String copy(excuse);
  std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
  std::replace_if(copy.begin(), copy.end(), notIsAlpha, ' ');

  SS ss;
  ss << copy;
  while(ss >> copy) {
    //std::cerr << "Checking '" << copy << "'" << std::endl;
    if(keywords.find(copy) != keywords.end())
      --ret;
  }

  //std::cerr << "Excuse '" << excuse << "': " << ret << std::endl;
  return ret;
}

String readLine(bool replace) {
  char w[309];
  gets(w);
  if(!replace)
    return String(w);
  for(int j = 0; true; ++j) {
    if(!isprint(w[j])) {
      w[j] = '\0';
      break;
    }
  }
  return String(w);
}

int main() {
  int K, E; // Keywords, excuses.

  for(int cas = 1; true; ++cas) {
    String s = readLine(false);
    SS ss; ss << s; 
    if(!(ss >> K >> E))
      return 0;

    Set keywords;
    for(int i = 0; i < K; ++i)
      keywords.insert(readLine(true));
    
    Excuse *excuses = new Excuse[E];
    for(int i = 0; i < E; ++i) {
      s = readLine(true);
      excuses[i] = Excuse(badness(s, keywords, K), s);
    }
    std::sort(excuses, excuses+E);

    std::cout << "Excuse Set #" << cas << std::endl;
    for(int i = 0; i < E && excuses[i].first == excuses[0].first; ++i)
      std::cout << excuses[i].second << std::endl;
    std::cout << std::endl;
  }
}
