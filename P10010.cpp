#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <map>

void readInts(int &a, int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      if(aDone)
	b = b*10 + (w[i]-'0');
      else {
	a = a*10 + (w[i]-'0');
	aStarted = true;
      }
    }
    else {
      if(!isprint(w[i]))
	break;
      if(aStarted)
	aDone = true;
    }
  }
}

void readInt(int &a) {
  a = 0;
  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      a = a*10 + (w[i]-'0');
    }
    else {
      if(!isprint(w[i]))
	break;
    }
  }
}

struct TrieNode; // Forward declaration.
typedef std::pair<int,int> Label;
typedef std::map<char,TrieNode*> NodeMap;

struct TrieNode {
  Label label;
  char letter;
  NodeMap children;

  ~TrieNode() {
    for(NodeMap::iterator it = children.begin(); it != children.end(); ++it) {
      TrieNode *child = it->second;
      delete child;
    }
    children.clear();
  }
};

class Trie {
  TrieNode root;
  
public:
  Trie() {
    root.letter = '\0'; // invalid char.
    root.label = Label(-1,-1); // Invalid label.
  }

  void addAllUpTo(char const * const word, const int len, const Label &label) {
    TrieNode *t = &root;
    for(int l = 0; l < len; ++l) {
      if(t->children.find(word[l]) == t->children.end()) {
	TrieNode *newT = new TrieNode();
	newT->label = label;
	newT->letter = word[l];
	t->children.insert(std::make_pair(word[l], newT));
      }
      t = t->children.find(word[l])->second;
    }
  }

  bool contains(char const * const word, Label &label) const {
    TrieNode const * t = &root;
    char c;
    for(int i = 0; isprint(c = word[i]); ++i) {
      if(t->children.find(word[i]) == t->children.end()) {
	return false;
      }
      t = t->children.find(word[i])->second;
    }
    label = t->label;
    return true;
  }
};

void buildTrie(Trie &trie, char const * const M, const int n, const int m) {
  int dirXs[8] = {-1,0,1,-1,1,-1,0,1};
  int dirYs[8] = {-1,-1,-1,0,0,1,1,1};
  char w[59];

  for(int y = 0; y < m; ++y)  {
    for(int x = 0; x < n; ++x) {
      Label label(x+1, y+1);
      // For each direction:
      for(int dirI = 0; dirI < 8; ++ dirI) {
	int dirX = dirXs[dirI];
	int dirY = dirYs[dirI];

	int xx = x;
	int yy = y;
	int i = 0;
	for(; xx >= 0 && yy >= 0 && xx < n && yy < m; ++i,xx=x+dirX*i,yy=y+dirY*i)
	  w[i] = M[n*yy+xx];
	w[i] = '\0';
	//std::cerr << "Adding word '" << w << "'" << std::endl;
	trie.addAllUpTo(w, i, label);
      } // for int dir
    } // for x
  } // for y
}

// n = line length (max x)
// m = number of lines (max y)
int main() {
  char M[2509], q[100];

  int cases, n, m, k;
  readInt(cases);
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    // Read data:
    gets(M); // ignore blank
    readInts(m, n);
    for(int i = 0; i < m; ++i) {
      gets(M+i*n);
    }
    std::transform(M,M+n*m,M,::tolower);

    // Build TRIE:
    Trie t;
    //std::cerr << "Building trie for M of size " << n << " x " << m << std::endl;
    buildTrie(t, M, n, m);
    //std::cerr << "Done building trie for M of size " << n << " x " << m << std::endl;

    // Perform queries:
    readInt(k);
    for(int i = 0; i < k; ++i) {
      gets(q);
      std::transform(q,q+100,q,::tolower);
      Label found;
      t.contains(q, found);
      std::cout << found.second << " " << found.first << std::endl;
    }
  }
  return 0;
}
