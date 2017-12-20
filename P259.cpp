struct PermutationNode {
  PermutationNode *next;
  char c;
};
struct PermutationHandler {
  PermutationNode *nodes;
  
  PermutationHandler(int size, char *c) {
    nodes = new PermutationNode[size+1];
    for(int i = 0; i < size; ++i) {
      nodes[i+1].c = c[i];
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

char perm[10];
bool ok[10][26];

bool run(const int i, PermutationHandler &ph) {
  if(i == 10) {
    return true;
  }

  // try all combinations:
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    perm[i] = n->c;
    if((n->c == '_' || ok[i][n->c-'A']) && run(i+1, ph))
      return true;

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
  return false;
}

int main() {
  char input[10];
  string s;

  while(true) {
    // Reset data:
    FORI(10) {
      FORJ(26)
	ok[i][j] = false;
    }
    int idx = 0;
    // Read input:
    while(true) {
      if(!getline(cin, s) || s.empty())
	break;
      stringstream ss; ss << s; ss >> s;
      char process = s[0];
      int multiplier = s[1]-'0';
      ss >> s; // valid machines
      FORUI(s.size()-1)
	ok[s[i]-'0'][process-'A'] = true;
      FORI(multiplier)
	input[idx++] = process;
    }
    if(idx == 0)
      return 0;
    while(idx < 10)
      input[idx++] = '_';
    PermutationHandler ph(10, input);
    if(!run(0, ph))
      cout << "!" << endl;
    else {
      FORI(10)
	cout << perm[i];
      cout << endl;
    }    
  } // while true
} // int main
