// Remove "happiness units by sitting next to " and "would " from input
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

int cost[10][10], perm[10], N = 0, best = -99999;

void compute(const int n, PermutationHandler &ph) {
  if(n == N) {
    int sum = 0;
    FORI(N) {
      int a = perm[i];
      int b = perm[(i+1)%N];
      sum += cost[a][b] + cost[b][a];
    }
    best = max(best, sum);
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *node2 = node->next;    
    // remove n from permutation:
    node->next = node2->next;
    perm[n] = node2->val;
    compute(n+1, ph);
    // re-insert in permutation and go to next:
    node->next = node2; // n->next is already set (never changes)
    node = node2;
  }
}

int main() {
  FORI(10) {
    FORJ(10) {
      cost[i][j] = 0;
    }
  }
  map<string,int> m;

  string a, b, op;
  int v;
  while(cin >> a >> op >> v >> b) {
    if(m.find(a) == m.end()) {
      m[a] = (int)m.size();
    }
    if(m.find(b) == m.end()) {
      m[b] = (int)m.size();
    }
    cost[m[a]][m[b]] = op == "gain" ? v : -v;
  }
  N = (int)m.size();
  N++; // Don't do this for part 1
  cout << "N=" << N << endl;

  PermutationHandler ph(N);
  compute(0, ph);
  cout << "Answer: " << best << endl;
}
