#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>

using namespace std;

struct PermutationNode {
  PermutationNode *next;
  string name;
  int x, y;
};
struct PermutationHandler {
  PermutationNode *nodes;
  
  PermutationHandler(int size) {
    nodes = new PermutationNode[size+1];
    for(int i = 0; i < size; ++i) {
      cin >> nodes[i+1].name >> nodes[i+1].x >> nodes[i+1].y;
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

double dist(PermutationNode const * const a, PermutationNode const * const b) {
  int dx = a->x - b->x;
  int dy = a->y - b->y;
  return sqrt(dx*dx+dy*dy);
}

void run(const int i, const int k, const double cur, double &best, PermutationNode const * const prev, PermutationHandler &ph) {
  if(i == k) {
    if(cur < best)
      best = cur;
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    if(i % 2 == 0) {
      run(i+1, k, cur, best, n, ph);
    }
    else {
      double add = dist(prev, n);
      if(node->name < n->name && cur + add < best) {
	run(i+1, k, cur+add, best, NULL, ph);
      }
    }

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int main() {
  int size;
  for(int cas = 1; true; ++cas) {
    cin >> size;
    if(size == 0)
      return 0;
    PermutationHandler ph(2*size);
    double best = 10000000, cur = 0;
    run(0, 2*size, cur, best, NULL, ph);
    printf("Case %d: %.2lf\n", cas, best);
  }
}
