#define RADIUS second

struct PermutationNode {
  PermutationNode *next;
  double radius;
};
struct PermutationHandler {
  PermutationNode *nodes;
  
  PermutationHandler(int size, double *radii) {
    nodes = new PermutationNode[size+1];
    for(int i = 0; i < size; ++i) {
      nodes[i+1].radius = radii[i];
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

// oO
double delta(double r1, double r2) {
  if(r1 > r2)
    swap(r1, r2);
  double R = r1+r2;
  double r = r2-r1;
  return sqrt(R*R-r*r);
}

void findOptimalPacking(const int i, const int N, PD *perm, double &bestWidth, PermutationHandler &ph) {
  if(i == N) {
    double maxWidth = 0;
    FORJ(N) {
      double candidate = perm[j].XX + perm[j].RADIUS;
      maxWidth = MAX(maxWidth, candidate);
    }
    /*if(maxWidth < bestWidth) {
      cerr << "Found better packing: " << maxWidth << endl;
      FORJ(N) {
	cerr << " r=" << perm[j].RADIUS << "@" << perm[j].XX;
      }
      cerr << endl;
    }//*/
    bestWidth = MIN(maxWidth, bestWidth);
    return;
  }

  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    double newRadius = n->radius;
    double newX = newRadius;
    FORJ(i) {
      double xx = perm[j].XX + delta(perm[j].RADIUS, newRadius);
      newX = MAX(xx, newX);
    }
    perm[i].XX = newX;
    perm[i].RADIUS = newRadius;
    findOptimalPacking(i+1, N, perm, bestWidth, ph);

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int main() {
  PD perm[10];
  double radii[10];
  FORCAS {
    int N; cin >> N;
    double maxRadius = 0;
    FORI(N) {
      cin >> radii[i];
      maxRadius = MAX(maxRadius, radii[i]);
    }
    PermutationHandler ph(N, radii);
    double bestWidth = 2*maxRadius*N;
    findOptimalPacking(0, N, perm, bestWidth, ph);
    printf("%.3lf\n", bestWidth);
  }
  return 0;
}
