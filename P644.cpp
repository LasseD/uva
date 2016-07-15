#include <iostream>
#include <stdio.h>

typedef std::pair<short,short> TrieNode;
#define EMPTY -1
#define zero first
#define one second

class Trie {
  TrieNode nodes[100];
  int size;
  
public:
  void reset() {
    nodes[0].zero = EMPTY;
    nodes[0].one = EMPTY;    
    size = 1;
  }

  // Return ok.
  bool addWord(char const * const w) {
    //std::cerr << "Adding word " << w << std::endl;
    TrieNode *t = nodes;
    char c;
    bool startedOwnPath = false;
    for(int i = 0; (c = w[i]) == '0' || c == '1'; ++i) {
      if(!startedOwnPath && i > 0 && t->zero == EMPTY && t->one == EMPTY) {
	//std::cerr << "Something else ended on position " << i << ". Returning false!" << std::endl;
	return false; // there is another code that is a suffix of this!
      }
      if(c == '0') {
	if(t->zero == EMPTY) {
	  startedOwnPath = true;
	  nodes[size].zero = EMPTY;
	  nodes[size].one = EMPTY;
	  t->zero = size;
	  ++size;
	}
	t = &nodes[t->zero];
      }
      else {
	if(t->one == EMPTY) {
	  startedOwnPath = true;
	  nodes[size].zero = EMPTY;
	  nodes[size].one = EMPTY;
	  t->one = size;
	  ++size;
	}
	t = &nodes[t->one];
      }
    }
    //std::cerr << "Returning " << startedOwnPath << std::endl;
    return startedOwnPath;
  }
};

int main() {
  char w[29];
  Trie t;

  for(int cas = 1; true; ++cas) {
    bool ok = true;
    t.reset();
    while(true) {
      if(!gets(w))
	return 0;
      if(w[0] == '9')
	break;
      if(ok)
	ok = t.addWord(w);
    }
    if(ok)
      std::cout << "Set " << cas << " is immediately decodable" << std::endl;
    else
      std::cout << "Set " << cas << " is not immediately decodable" << std::endl;
  }
  return 0;
}
