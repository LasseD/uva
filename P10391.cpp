struct Node {
  bool terminal;
  Node* n[26];

  Node() : terminal(false) {
    FORI(26)
      n[i] = NULL;
  }
  Node(const Node &o) : terminal(o.terminal) {
    FORI(26)
      n[i] = o.n[i];
  }
};

void addWord(Node *n, string &s, unsigned int idx) {
  if(idx == s.size()) {
    n->terminal = true;
    return;
  }
  int ni = s[idx]-'a';
  if(n->n[ni] == NULL) {
    n->n[ni] = new Node();
  }
  addWord(n->n[ni], s, idx+1);
}

void go(Node *n, Node *rn, int *word, bool *terminals, int curLetter, unsigned int idx) {
  terminals[idx] = n->terminal;
  word[idx] = curLetter;

  if(n->terminal) {
    // Find all terminals below and report if rn contains them:
    Node *revNode = rn;
    for(int i = (int)idx; i > 0; --i) {
      revNode = revNode->n[word[i]];
      if(revNode == NULL)
	break; // Can't walk.
      if(revNode->terminal && terminals[i-1]) {
	FORUJ(idx+1)
	  cout << (char)(word[j]+'a');
	cout << endl;
	//cerr << "Found at i=" << i << ", idx=" << idx << endl;
	break; // Found!
      }
    }
  }
  
  FORI(26) {
    if(n->n[i] != NULL)
      go(n->n[i], rn, word, terminals, i, idx+1);
  }
}

int main() {
  Node words, rwords;
  
  string s;
  unsigned int maxWordLength = 0;
  while(cin >> s) {
    addWord(&words, s, 0);
    for(int i = 0, ri = (int)s.size()-1; i < ri; ++i, --ri)
      swap(s[i], s[ri]);
    addWord(&rwords, s, 0);
    if(s.size() > maxWordLength)
      maxWordLength = s.size();
  }

  int *word = new int[maxWordLength];
  bool *terminals = new bool[maxWordLength];
  FORI(26) {
    if(words.n[i] == NULL)
      continue;
    go(words.n[i], &rwords, word, terminals, i, 0);
  }
}
