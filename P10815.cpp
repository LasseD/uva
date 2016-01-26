#include <iostream>
#include <stdio.h>
#include <set>
#include <algorithm>

std::string clean(char *c) {
  std::string copy(c);
  std::transform(copy.begin(),copy.end(),copy.begin(),::tolower);
  return copy;
}

int main() {
  char c, line[209];
  std::set<std::string> dictionary;

  while(gets(line)) {
    int start = 0;
    for(int i = 0; true; ++i) {
      c = line[i];
      if(isalpha(c))
	continue;
      if(i > start) {
	line[i] = '\0';
	std::string s = clean(&line[start]);
	if(dictionary.find(s) == dictionary.end())
	  dictionary.insert(s);
      }
      start = i+1;
      if(!isprint(c))
	break;
    }    
  }
  for(std::set<std::string>::const_iterator it = dictionary.begin(); it != dictionary.end(); ++it)
    std::cout << *it << std::endl;
  return 0;
}
