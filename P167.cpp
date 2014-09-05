#include <iostream>
#include <stdio.h>

/*
Define Permutation:
8 queens on board, one in each row/colummn [0;7].
Assume permutation of columns.
Permutation a b c ... means:
column with queen on row a at column 0.
column with queen on row b at column 1.
...
 */
struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode nodes[9];
  
  void reset(int size) {
    for(int i = 0; i < size; ++i) {
      nodes[i+1].val = i;
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[size].next = NULL;
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

bool boardOK(int * const perm, int set = 8) {
  // simply check diagonals:
  bool bL[8], bTL[8], bTR[8], bR[8];
  for(int i = 0; i < 8; ++i){
    bL[i] = bTL[i] = bTR[i] = bR[i] = false;
  }

  for(int column = 0; column < set; ++column) {
    int row = perm[column];
    // check 4 edge positions:
    {
      // up /:
      int columnTop = column + row;
      if(columnTop < 8) {
	if(bTR[columnTop]) {
	  return false;
	}
	bTR[columnTop] = true;
      }
      else { // hits side:
	int rowT = columnTop-8;
	if(bR[rowT]) {
	  return false;
	}
	bR[rowT] = true;
      }
    }
    {
      // up \:
      int columnTop = column - row;
      if(columnTop >= 0) {
	if(bTL[columnTop]) {
	  return false;
	}
	bTL[columnTop] = true;
      }
      else { // hits side:
	int rowT = -columnTop;
	if(bL[rowT]) {
	  return false;
	}
	bL[rowT] = true;
      }
    }
  }
  return true;
}

int val(int const * const board, int * const permutation) {
  int res = 0;
  for(int i = 0; i < 8; ++i) {
    res += board[i + 8*permutation[i]];
  }
  return res;
}

void run(const int i, int const * const board, int * const permutation, int &best, PermutationHandler &ph) {
  if(i == 7) {
    int lastQueen = ph.root()->next->val;
    permutation[7] = lastQueen;

    if(boardOK(permutation)) {
      best = std::max(best, val(board, permutation));
    }
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    permutation[i] = n->val;
    if(boardOK(permutation, i+1))
      run(i+1, board, permutation, best, ph);

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int get(int *board) {
  int res = 0;
  int permutation[8];
  PermutationHandler ph;
  ph.reset(8);
  run(0, board, permutation, res, ph);
  return res;
}

int main() {
  int N;
  int board[64];
  std::cin >> N;
  for(int ignore = 0; ignore < N; ++ignore) {
    for(int i = 0; i < 64; ++i) {
      std::cin >> board[i];
    }

    int res = get(board);
    printf("%5i\n", res);
  }
}
