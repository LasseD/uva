#include <stdio.h>
#include <iostream>
#include <set>

int abs(int a) {
  if(a < 0)
    return -a;
  return a;
}
int max(int a, int b) {
  if(a < b)
    return b;
  return a;
}

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

int iterations = 0;

inline int getPartialBandwidthAdd(int i, bool const * const V, int const * const numbering, int * const pos) {
  int ni = numbering[i];

  int res = 0;
  for(int j = 0; j < i; ++j) {
    int nj = numbering[j];
    if(V[ni*8+nj] && abs(pos[ni]-pos[nj]) > res) {
      res = abs(pos[ni]-pos[nj]);
    }
  }
  return res;
}

void run(const int i, bool const * const V, int * const numbering, int &bestBandwidth, int * const bestNumbering, PermutationHandler &ph, const int size, const int lowerBound, int * const pos, const int partialBandWidth) {
  ///std::cerr << "run i: " << i << " size: " << size << " bb: " << bestBandwidth << " lb: " << lowerBound << " pb: " << partialBandWidth << std::endl;
  if(i == size-1) {
    //++iterations;
    int letter = ph.root()->next->val;
    numbering[i] = letter;
    pos[letter] = i;
    int bw = max(partialBandWidth, getPartialBandwidthAdd(i, V, numbering, pos));
    
    if(bw < bestBandwidth) {
      bestBandwidth = bw;
      for(int j = 0; j < size; ++j) {
	bestNumbering[j] = numbering[j];
	///std::cerr << " " << numbering[j];
      }
      ///std::cerr << " -> " << bw << std::endl;
    }//*/
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    numbering[i] = n->val;
    pos[numbering[i]] = i;

    int bw = max(partialBandWidth, getPartialBandwidthAdd(i, V, numbering, pos));
    run(i+1, V, numbering, bestBandwidth, bestNumbering, ph, size, lowerBound, pos, bw);
    if(bestBandwidth == lowerBound)
      return; // ph might be corrupt

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

int main() {
  std::string line;
  bool V[64];
  int numbering[8];
  int bestNumbering[8];
  PermutationHandler ph;
  int pos[8];
  char rmap[8];
  int map['Z'+1];
  unsigned int i;
  
  while(std::getline(std::cin, line)) {
    // reset state:
    for(i = 0; i < 64; ++i) {
      V[i] = false;
    }
    for(i = 0; i < 8; ++i) {
      bestNumbering[i] = i;
      pos[i] = i;
    }
    
    // preparse line:
    std::set<char> chars;
    unsigned int lineSize = 0;
    for(i = 0; i < line.size(); ++i) {
      char c = line[i];
      if(c >= 'A' && c <= 'Z') {
	chars.insert(c);
	line[lineSize++] = c;
      }
      else if(c == ';' || c == ':') {
	line[lineSize++] = c;	
      }
      else if(c == '#') {
	//std::cerr << "Iterations: " << iterations<< std::endl;
        return 0;
      }
    }
    ///std::cerr << "Reading line: '" << line << "'" << std::endl;

    unsigned int size = chars.size();
    ph.reset(size);
    i = 0;
    for(std::set<char>::const_iterator it = chars.begin(); it != chars.end(); ++it, ++i) {
      map[(int)(*it)] = i;
      rmap[i] = *it;
    }
    // parse line:
    int activeLead = map[(int)(line[0])];
    char c;
    for(i = 2; i < lineSize; ++i) {
      c = line[i];
      if(c == ';') {
	++i;
	c = line[i];
	activeLead = map[(int)c];	  
	++i; // skip ':'
      }
      else {
	int posI = map[(int)c];	  
	///std::cerr << rmap[activeLead] << "->" << c << " (@" << posI << ")" << std::endl;
	V[posI*8+activeLead] = V[posI+activeLead*8] = true;
      }
    }
    
    int maxConnections = 0;
    int minConnections = 7;
    for(i = 0; i < size; ++i) {
      int connections = 0;
      for(unsigned int j = 0; j < size; ++j) {
	if(i != j && V[i+8*j])
	  ++connections;
      }
      if(connections > maxConnections)
	maxConnections = connections;
      if(connections < minConnections)
	minConnections = connections;
    }
    const int lowerBound = max(minConnections, (1+maxConnections)/2);

    // compute:
    int bestBandwidth = 7;
    run(0, V, numbering, bestBandwidth, bestNumbering, ph, size, lowerBound, pos, 0);
    for(i = 0; i < size; ++i) {
      ///std::cerr << "(" << bestNumbering[i] << ")";
      printf("%c ", rmap[bestNumbering[i]]);
    }
    printf("-> %i\n", bestBandwidth);
    //std::cerr << "Iterations: " << iterations << " lower bound: " << lowerBound << std::endl;
    //iterations = 0;
  }
  return 1;
}
