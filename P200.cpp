#include <iostream>
#include <stdio.h>

int main() {
  bool inUse[26];
  int in[26];
  bool before[26*26];
  for(int i = 0; i < 26; ++i) {
    inUse[i] = false;
    in[i] = 0;
  }
  for(int i = 0; i < 26*26; ++i) {
    before[i] = false;
  }
  
  std::string word, prev;
  while(true) {
    std::cin >> word;
    if(word[0] == '#')
      break;
    for(unsigned int i = 0; i < word.size(); ++i) {      
      inUse[word[i]-'A'] = true;
    }
    for(unsigned int i = 0; i < word.size() && i < prev.size(); ++i) {      
      if(prev[i] != word[i]) {
	int fromI = prev[i]-'A';
	int toI = word[i]-'A';
	if(!before[26*fromI+toI]) {
	  before[26*fromI+toI] = true;
	  ++in[toI];
	  //std::cerr << "Setting relation: " << prev[i] << " -> " << word[i] << std::endl;
	}
	break;
      }
    }
    prev = word;
  }
  int noIn = -1;
  for(int i = 0; i < 26; ++i) {
    if(inUse[i] && in[i] == 0) {
      noIn = i;
      break;
    }
  }
  while(noIn != -1) {
    std::cout << (char)(noIn+'A');
    int newNoIn = -1;
    for(int i = 0; i < 26; ++i) {
      if(i == noIn)
	continue;
      if(before[noIn*26+i]) {
	--in[i];
	if(in[i] == 0)
	  newNoIn = i;
      }
    }
    noIn = newNoIn;
  }
  std::cout << std::endl;
  return 0;
}
