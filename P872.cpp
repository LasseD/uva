struct PermutationNode {
  PermutationNode *next;
  int val;  
};
struct PermutationHandler {
  PermutationNode *nodes;  
  PermutationHandler(vector<char> &data) {
    nodes = new PermutationNode[data.size()+1];
    FORUI(data.size()) {
      nodes[i+1].val = data[i];
      nodes[i].next = &(nodes[i+1]);
    }
    nodes[data.size()].next = NULL;
  }
  ~PermutationHandler() {
    delete[] nodes;
  }
  PermutationNode* root() {
    return &(nodes[0]);
  }
};

bool go(const int i, const int N, bool const * const constraints, char * const perm, PermutationHandler &ph) {
  if(i == N) {
    FORJ(N) {
      if(j != 0)
	cout << " ";
      cout << perm[j];
    }
    cout << endl;
    return true;
  }
  // try all combinations:
  bool ret = false;
  PermutationNode *node = ph.root();
  while(node->next != NULL) {
    PermutationNode *n = node->next;    
    // remove n from permutation:
    node->next = n->next;

    perm[i] = n->val;
    bool ok = true;
    FORJ(i) {
      if(constraints[26*(perm[j]-'A')+perm[i]-'A']) {
	ok = false;
	break;
      }
    }
    if(ok)
      ret |= go(i+1, N, constraints, perm, ph);

    // re-insert in permutation and go to next:
    node->next = n; // n->next is already set (never changes)
    node = n;
  }
  return ret;
}

int main() {
  int cases = 0;
  char c, line[209], perm[20];
  bool constraints[26*26];
  gets(line);
  FORK(isdigit(c = line[k]))
    cases = 10*cases + c-'0';
  //scanf("%d\n", &cases);
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;
    gets(line); // empty line
    gets(line); // characters
    vector<char> letters;
    for(int i = 0; isprint(c = line[i]); ++i) {
      if(c >= 'A' && c <= 'Z') {
	letters.push_back(c);
      }
    }
    sort(letters.begin(), letters.end());
    // Read restrictions:
    memset(constraints, false, 26*26*sizeof(bool));
    gets(line); // Constraints.
    string s(line);
    stringstream ss;
    ss << s;
    while(ss >> s)
      constraints[26*(s[2]-'A')+s[0]-'A'] = true;      

    PermutationHandler ph(letters);
    bool any = go(0, (int)letters.size(), constraints, perm, ph);
    if(!any)
      cout << "NO" << endl;
  }
  return 0;
}
