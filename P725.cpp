#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<int,int> ND;

struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode nodes[11];
  
  void reset() {
    for(int i = 0; i < 10; ++i) {
      nodes[i+1].val = i;
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[10].next = NULL;
  }

  PermutationNode* root() {
    return &(nodes[0]);
  }
};

void handlePermutation(int const * const permutation, std::vector<ND> *v) {
  int n = 0, d = 0;
  for(int i = 0; i < 5; ++i) {
    n = 10*n + permutation[i];
    d = 10*d + permutation[5+i];
  }
  int fraction = n/d;
  if((n != fraction * d) || fraction < 2 || fraction > 79)
    return;
  v[fraction-2].push_back(ND(n,d));
}

void run(const int i, int * const permutation, std::vector<ND> *v, PermutationHandler &ph) {
  if(i == 9) {
    int last = ph.root()->next->val;
    permutation[9] = last;

    // Main computation:
    handlePermutation(permutation, v);
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    permutation[i] = n->val;
    run(i+1, permutation, v, ph);

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

void outN(int n) {
  if(n < 10000)
    std::cout << "0";
  std::cout << n;
}

int main() {
  PermutationHandler ph;
  int permutation[10]; // = {0,1,2,3,4,5,6,7,8,9};
  std::vector<ND> v[78];

  ph.reset();
  run(0, permutation, v, ph);
  for(int i = 0; i < 78; ++i) {
    std::sort(v[i].begin(), v[i].end());
  }

  bool first = true;
  while(true) {
    int N;
    std::cin >> N;
    if(N == 0)
      return 0;
    if(!first)
      std::cout << std::endl;
    if(N < 2 || N > 79 || v[N-2].empty()) {
      std::cout << "There are no solutions for " << N << "." << std::endl;
    }
    else {
      for(std::vector<ND>::const_iterator it = v[N-2].begin(); it != v[N-2].end(); ++it) {
	outN(it->first);
	std::cout << " / ";
	outN(it->second);
	std::cout << " = " << N << std::endl;
      }
    }
    
    first = false;
  }
}
