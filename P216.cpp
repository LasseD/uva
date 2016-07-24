#include <iostream>
#include <stdio.h>
#include <math.h>

typedef std::pair<int,int> Point;
#define X first
#define Y second

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

int distSq(const Point &p1, const Point &p2) {
  return (p1.X-p2.X)*(p1.X-p2.X) + (p1.Y-p2.Y)*(p1.Y-p2.Y);
}

double dist(Point const * const positions, int i, int j) {
  return 16.0 + sqrt(distSq(positions[i], positions[j]));
}

void compute(const int i, const int N, Point const * const positions, int * const perm, const double permScore, int * const bestPerm, double &bestPermScore, PermutationHandler &ph) {
  if(i == N) {
    if(bestPermScore < 0 || permScore < bestPermScore) {
      bestPermScore = permScore;
      for(int j = 0; j < N; ++j)
	bestPerm[j] = perm[j];
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
    double add = i == 0 ? 0 : dist(positions, perm[i-1], perm[i]);
    compute(i+1, N, positions, perm, permScore+add, bestPerm, bestPermScore, ph);

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int main() {
  int N, perm[8], bestPerm[8];
  Point positions[8];
  for(int cas = 1; true; ++cas) {
    std::cin >> N;
    if(N == 0)
      return 0;
    printf("**********************************************************\n");
    printf("Network #%d\n", cas);
    for(int i = 0; i < N; ++i)
      std::cin >> positions[i].X >> positions[i].Y;

    PermutationHandler ph(N);
    double bestScore = -1;
    compute(0, N, positions, perm, 0, bestPerm, bestScore, ph);
    // Output:
    for(int i = 1; i < N; ++i) {
      double d = dist(positions, bestPerm[i-1], bestPerm[i]);
      printf("Cable requirement to connect (%d,%d) to (%d,%d) is %.2lf feet.\n", positions[bestPerm[i-1]].X, positions[bestPerm[i-1]].Y, positions[bestPerm[i]].X, positions[bestPerm[i]].Y, d);
            
    }
    printf("Number of feet of cable required is %.2lf.\n", bestScore);
  }
}
