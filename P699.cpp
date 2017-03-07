struct Node {
  Node *L, *R;
  int val;
};

Node* read() {
  int val; cin >> val;
  if(val == -1)
    return NULL;
  Node *n = new Node();
  n->val = val;
  n->L = read();
  n->R = read();
  return n;
}

void write(Node *n, int *ret, int pos) {
  ret[pos] += n->val;
  if(n->L != NULL)
    write(n->L, ret, pos-1);
  if(n->R != NULL)
    write(n->R, ret, pos+1);
}

void kill(Node *n) {
  if(n->L != NULL)
    kill(n->L);
  if(n->R != NULL)
    kill(n->R);
  delete n;
}

int main() {
  int ret[400]; // root start at 200.
  for(int cas = 1; true; ++cas) {
    // Read tree:
    Node *root = read();
    if(root == NULL)
      return 0;
    memset(ret, 0, 400*sizeof(int));
    write(root, ret, 200);
    cout << "Case " << cas << ":" << endl;
    bool first = true;
    FORI(400) {
      if(ret[i] != 0) {
	if(!first)
	  cout << " ";
	cout << ret[i];
	first = false;
      }
    }
    cout << endl << endl;
    kill(root);
  }
}
