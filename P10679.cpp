#include <iostream>
#include <stdio.h>

#define NUM_CHILDREN ('z'-'A'+1)

/*
See:
http://stackoverflow.com/questions/9452701/ukkonens-suffix-tree-algorithm-in-plain-english
http://pastie.org/5925809
 */

struct SuffixTreeNode {
  char const *c;
  int len;
  SuffixTreeNode *children[NUM_CHILDREN];

  void reset() {
    for(int i = 0; i < NUM_CHILDREN; ++i)
      children[i] = NULL;
  }

  void print() const {
    for(int i = 0; i < len; ++i)
      std::cerr << c[i];
    std::cerr<< " [";
    for(int i = 0; i < NUM_CHILDREN; ++i) {
      if(children[i] != NULL)
	std::cerr << (char)('A'+i);
    }
    std::cerr<< "]";
  }
};

class SuffixTree {
  SuffixTreeNode *nodes;
  int size;
  
public:
  void print() const {
    std::cerr << "Size: " << size << " SuffixTree nodes: " << std::endl;
    for(int i = 0; i < size; ++i) {
      std::cerr << " " << i << ": ";
      nodes[i].print();
      std::cerr << std::endl;
    }
  }

  void addString(char const * const S, int len) {
    SuffixTreeNode *t = &nodes[0];
    int ti = 0;
    for(int Si = 0; Si < len; ++Si, ++ti) {
      if(ti == t->len) {
	// Find next t:
	if(t->children[S[Si]-'A'] == NULL) {
	  nodes[size].reset();
	  nodes[size].len = len-Si;
	  nodes[size].c = &S[Si];
	  t->children[S[Si]-'A'] = &nodes[size];
	  ++size;
	  return;
	}
	t = t->children[S[Si]-'A'];
	ti = 0;	// t updated!
      }

      char tc = t->c[ti];
      if(tc != S[Si]) { // Split t:
	// Construct new suffix node and update t:
	for(int i = 0; i < NUM_CHILDREN; ++i) {
	  nodes[size].children[i] = t->children[i];
	  t->children[i] = NULL;
	}
	t->children[tc-'A'] = &nodes[size];
	nodes[size].len = t->len - ti;
	t->len = ti;
	nodes[size].c = &t->c[ti];
	++size;
	
	// Construct new node for rest of S:
	t->children[S[Si]-'A'] = &nodes[size];
	nodes[size].reset();
	nodes[size].c = &S[Si];
	nodes[size].len = len-Si;	
	++size;
	return;
      }
    }
  }

  void reset(char const * const S, int len) {
    nodes[0].reset();
    nodes[0].len = 0;
    nodes[0].c = NULL;
    size = 1;

    for(int i = 0; len-i >= 1; ++i) {
      addString(&S[i], len-i);
      /*std::cerr << "After adding " << &S[i] << ": " << std::endl;
      print();//*/
    }    
  }

  SuffixTree() {
    nodes = new SuffixTreeNode[10009];
  }
  ~SuffixTree() {
    delete[] nodes;
  }

  bool contains(char const * const T) const { 
    SuffixTreeNode const * t = nodes;
    int ti = 0;
    char c;
    for(int i = 0; isalpha(c = T[i]); ++i, ++ti) {
      if(ti >= t->len) {
	t = t->children[c-'A'];
	if(t == NULL)
	  return false;
	ti = 0;
      }
      if(T[i] != t->c[ti])
	return false;
    }
    return true;
  }
};

int main() {
  int k, q;
  std::string S, T;
  SuffixTree t;

  std::cin >> k;
  for(int cas = 0; cas < k; ++cas) {
    std::cin >> S;
    int len = 0;
    while(isalpha(S[len]))
      ++len;

    t.reset(S.c_str(), len);
    std::cin >> q;
    for(int i = 0; i < q; ++i) {
      std::cin >> T;
      if(t.contains(T.c_str()))
	std::cout << "y" << std::endl;
      else
	std::cout << "n" << std::endl;
    }
  }
  return 0;
}
