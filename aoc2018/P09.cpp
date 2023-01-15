struct Marble {
  Marble *prev, *next;
  int val;
};

// Remove all by the numbers from the input!
int main() {
  int players, lastMarble;
  cin >> players >> lastMarble;
  LL *scores = new LL[players];
  FORI(players)
    scores[i] = 0;

  Marble *root = new Marble;
  root->next = root->prev = root;
  root->val = 0;
  Marble *cur = root;
  
  for(int i = 1; i <= lastMarble; i++) {
    if(i % 23 == 0) {
      scores[i%players]+=i;
      // Remove -7 ball!
      FORJ(7) {
	cur = cur->prev;
      }
      scores[i%players]+=cur->val;
      cur = cur->prev;
      cur->next = cur->next->next;
      cur->next->prev = cur;

      cur = cur->next;
    }
    else {
      // Insert marble i:
      cur = cur->next; // Insert after this.
      Marble *next = cur->next;
      
      Marble *m = new Marble;
      m->val = i;
      // Update 4 pointers:
      m->prev = cur;
      m->next = next;
      cur->next = next->prev = m;
      // Set new cur:
      cur = m;
    }
    
    if(i < 30) {
      cout << "[" << ((i-1)%players+1) << "] " << root->val;
      Marble *m = root->next;
      while(m != root) {
	if(m != m->next->prev || m->next == m || m->prev == m) {
	  cerr << "List broken!" << endl;
	  die();
	}
	if(m->val < 10)
	  cout << " ";
	if(m == cur)
	  cout << "(";
	else
	  cout << " ";
	cout << m->val;
	if(m == cur)
	  cout << ")";
	else
	  cout << " ";
	m = m->next;
      }
      cout << endl;
    }
  }
  LL bestScore = -1;
  FORI(players) {
    bestScore = max(scores[i], bestScore);
  }
  cout << bestScore << endl;
}
