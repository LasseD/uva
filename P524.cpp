#include <iostream>

struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode *nodes;
  PermutationHandler(int size) {
    nodes = new PermutationNode[size+1];
    for(int i = 0; i < size; ++i) {
      nodes[i+1].val = i+2;
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[size].next = NULL;
  }
  ~PermutationHandler() {
    delete[] nodes;
  }
  PermutationNode* root() {
    return &(nodes[0]);
  }
};

void findCircles(PermutationHandler &ph, int *perm, const int i, 
		 const int len, bool const * const primes) {
  if(i == len) {
    if(primes[1+perm[len-1]]) {
      std::cout << "1";
      for(int j = 1; j < len; ++j)
	std::cout << " " << perm[j];
      std::cout << std::endl;
    }
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    perm[i] = n->val;
    if(primes[perm[i-1]+n->val]) { // is prime.
      findCircles(ph, perm, i+1, len, primes);
    }

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int main() {
  bool primes[32] = {0,0,1,1,0,1,0,1,0,0, // 0-9
		     0,1,0,1,0,0,0,1,0,1, // 10-19
		     0,0,0,1,0,0,0,0,0,1, // 20-29
		     0,1}; // 30-31
  int permutation[16];
  permutation[0] = 1;

  int n;
  for(int cas = 1; std::cin >> n; ++cas) {
    if(cas != 1)
      std::cout << std::endl;
    std::cout << "Case " << cas << ":" << std::endl;
    if(n == 1) {
      std::cout << "1" << std::endl;
      continue;
    }
    PermutationHandler ph(n-1);
    findCircles(ph, permutation, 1, n, primes);
  }
}
