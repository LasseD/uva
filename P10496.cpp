struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode *nodes;
  
  PermutationHandler(int size) {
    nodes = new PermutationNode[size+1];
    for(int i = 0; i < size; ++i) {
      nodes[i+1].val = i;
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

int dist(const Point &a, const Point &b) {
  return ABS(a.XX-b.XX) + ABS(a.YY-b.YY);
}

void compute(const int i, const int N, const Point start, Point const * const positions, int * const perm, const int pathLength, int &bestPathLength, PermutationHandler &ph) {
  if(i == N) {
    int L = pathLength + dist(positions[perm[N-1]], start);
    if(bestPathLength > L) {
      bestPathLength = L;
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
    int newLength = pathLength;
    if(i > 0) {
      newLength += dist(positions[perm[i]], positions[perm[i-1]]);
    }
    else
      newLength = dist(positions[perm[i]], start);

    if(newLength < bestPathLength)
      compute(i+1, N, start, positions, perm, newLength, bestPathLength, ph);

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int main() {
  int w, h, n, perm[10];
  Point start, positions[10];
  FORCAS {
    cin >> w >> h; // ignored.
    cin >> start.XX >> start.YY;
    cin >> n;
    FORI(n)
      cin >> positions[i].XX >> positions[i].YY;
    PermutationHandler ph(n);
    int best = 999999;
    compute(0, n, start, positions, perm, 0, best, ph);
    printf("The shortest path has length %d\n", best);
  }
  return 0;
}
