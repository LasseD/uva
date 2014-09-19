#include <stdio.h>
#include <iostream>
#include <set>
#include <algorithm>

struct PermutationNode {
  PermutationNode *next;
  char val;  
};
struct PermutationHandler {
  PermutationNode *nodes;

  PermutationHandler() : nodes(NULL) {}

  void reset(const std::string &word) {
    if(nodes != NULL)
      delete[] nodes;
    nodes = new PermutationNode[word.size()+1];

    for(unsigned int i = 0; i < word.size(); ++i) {
      nodes[i+1].val = word[i];
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[word.size()].next = NULL;
  }

  PermutationNode* root() {
    return &(nodes[0]);
  }
};

void run(const unsigned int i, PermutationHandler &ph, std::string &word) {
  if(i == word.size()-1) {
    char letter = ph.root()->next->val;
    word[i] = letter;
    
    std::cout << word << std::endl;
    
    return;
  }
  // try all combinations:
  PermutationNode *node = ph.root();
  char prevChar = ' ';
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    char currentChar = n->val;
    word[i] = currentChar;

    if(currentChar != prevChar) {
      run(i+1, ph, word);
      prevChar = currentChar;
    }

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
}

bool ffs(char a,char b) { 
  if(('a' <= a && a <= 'z' && 'a' <= b && b <= 'z') || ('A' <= a && a <= 'Z' && 'A' <= b && b <= 'Z'))
    return a < b;
  if('a' <= a && a <= 'z') {
    a -= 'a'-'A';
    if(a == b)
      return false;
    return a < b;
  }
  b -= 'a'-'A';
  if(a == b)
    return true;
  return a < b;
}

int main() {
  std::string line;
  PermutationHandler ph;
  
  int lines;
  std::cin >> lines;

  for(int ignore = 0; ignore < lines; ++ignore) {
    std::cin >> line;

    ///std::cerr << "Reading word: '" << line << "'" << std::endl;
    std::sort(&line[0], &line[line.size()], ffs);
    ///std::cerr << "Init: '" << line << "'" << std::endl;
    ph.reset(line);
    run(0, ph, line);
  }
  return 0;
}
