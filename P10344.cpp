#include <iostream>
#include <stdio.h>

struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode nodes[6];
  
  void reset(int const * const row) {
    for(int i = 0; i < 5; ++i) {
      nodes[i+1].val = row[i];
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[5].next = NULL;
  }

  PermutationNode* root() {
    return &(nodes[0]);
  }
};

void printPerm(int * const perm, int set = 8) {
  std::cerr << " ";
  for(int c = 0; c < set; ++c) {
    std::cerr << (char)(c+'A');
  }
  std::cerr << std::endl;

  for(int r = 0; r < 8; ++r){
    std::cerr << (r+1);
    for(int c = 0; c < set; ++c) {
      if(perm[c] == r)
	std::cerr << "X";
      else
	std::cerr << "\\";
    }
    std::cerr << std::endl;
  }
}

bool any23(const int i, int leftResult, PermutationHandler &ph) {
  if(i == 5) {
    return leftResult == 23;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    if(i == 0) {
      if(any23(1, n->val, ph))
	return true;
    }
    else {
      if(any23(i+1, leftResult-n->val, ph) ||
	 any23(i+1, leftResult*n->val, ph) ||
	 any23(i+1, leftResult+n->val, ph))
	return true;
    }

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
  return false;
}

int main() {
  int row[5];
  PermutationHandler ph;
  while(true) {
    bool allZero = true;
    for(int i = 0; i < 5; ++i) {
      std::cin >> row[i];
      if(row[i] != 0)
	allZero = false;
    }
    if(allZero)
      return 0;
    ph.reset(row);
    if(any23(0, -1337, ph))
      std::cout << "Possible" << std::endl;
    else
      std::cout << "Impossible" << std::endl;
  }
}
