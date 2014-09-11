#include <iostream>
#include <stdio.h>
#include <algorithm>

typedef std::string str;

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

bool posOK(const str &plain, const str &cy1, const int i, const int k, const int to) {
  for(unsigned int j = 0; j < plain.size(); j+=k) {
    if(j+i >= plain.size())
      break;
    if(j+to >= plain.size())
      return false; // moving out of bounds and can't be padded correctly.
    if(plain[j+i] != cy1[j+to])
      return false;
  }
  return true;
}

bool findPermutation(const int i, const str &plain, const str &cy1, const int k, int *perm, PermutationHandler &ph) {
  if(i == k) {
    return true;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    perm[i] = n->val;
    if(posOK(plain, cy1, i, k, perm[i])) {
      if(findPermutation(i+1, plain, cy1, k, perm, ph)) {
	node->next = n;
	return true;
      }
    }

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
  return false;
}

int findPermutation(const str &plain, const str &cy1, int *perm) {
  const unsigned int n = plain.size();
  for(unsigned int k = 1; k <= n; ++k) {
    // Pass 1: check if letters sum to same:
    bool kOK = true;
    for(unsigned int i = 0; i < n; i += k) {
      long sum1 = 0;
      long sum2 = 0;
      for(unsigned int j = 0; j < k && i+j < n; ++j) {
	sum1 += plain[i+j];
	sum2 += cy1[i+j];
      }
      if(sum1 != sum2) {
	kOK = false;
	break;
      }
    }
    if(!kOK)
      continue;
    // Pass 2: check if same letters:
    str s1 = plain;
    str s2 = cy1;
    for(unsigned int i = 0; i < n && kOK; i += k) {
      unsigned int max = std::min(n, i+k);
      std::sort(&s1[i], &s1[max]);
      std::sort(&s2[i], &s2[max]);
      for(unsigned int j = 0; j < k && i+j < n; ++j) {
	if(s1[i+j] != s2[i+j]) {
	  kOK = false;
	  break;
	}
      }
    }
    if(!kOK)
      continue;
    // pass 3: Find permutation:
    PermutationHandler ph(k);
    if(findPermutation(0, plain, cy1, k, perm, ph))
      return k;
  }
  return 0;
}

char line[82];
str getL() {
  std::cin.getline(line, 82);
  for(int i = 0; i < 82; ++i) {
    if(line[i] == '\0')
      break;
    if(line[i] == '\r' || line[i] == '\n')
      line[i] = '\0';
  }
  return str(line);
}

str permute(const str &c2, int const * const perm, const int k) {
  str res(((c2.size()+k-1)/k)*k, '?');
  //std::cerr << "Performing permutation with k=" << k << " => |res|=" << res.size() << ": " << res << std::endl;
  for(unsigned int i = 0; i < c2.size(); i+=k) {
    for(int j = 0; j < k; ++j) {
      if(i+perm[j] < c2.size())
	res[i+j] = c2[i+perm[j]];
    }
  }
  return res;
}

int main() {
  int perm[80];
  while(true) {
    str plain = getL();
    if(plain == "#")
      return 0;
    str c1 = getL();
    str c2 = getL();
    int k = findPermutation(plain, c1, perm);
    if(k != 0) {
      c2 = permute(c2, perm, k);      
    }
    std::cout << c2 << std::endl;
  }
}
