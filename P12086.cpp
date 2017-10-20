struct Node {
  int low, high, val;
};

Node *tree;

int read(int low, int high, int nodeI) {
  Node &n = tree[nodeI];
  if(n.low > high || n.high < low)
    return 0;
  if(n.low >= low && n.high <= high)
    return n.val;
  return read(low, high, nodeI*2+1) + read(low, high, nodeI*2+2);
}

int main() {
  int N;
  for(int cas = 1; true; ++cas) {
    cin >> N;
    if(N == 0)
      return 0;
    if(cas != 1)
      cout << endl;
    cout << "Case " << cas << ":" << endl;
    // Build tree:
    tree = new Node[4*N];
    int rowSize = 1;
    int rowIdx = 0;
    while(rowSize < N) {
      rowIdx += rowSize;
      rowSize <<= 1;
    }

    // Read data and set tree info:
    FORI(rowSize) { // Insert all leafs and bump data up the tree:
      int nodeI = rowIdx + i;
      if(i >= N)
	tree[nodeI].val = 0;
      else
	cin >> tree[nodeI].val;
      tree[nodeI].low = tree[nodeI].high = i;
      // Bump data up as long as we are at a right child:
      int parentI;
      while(((parentI = (nodeI-1)/2)*2+2) == nodeI) { // while we are the right child:
	tree[parentI].low = tree[nodeI-1].low;
	tree[parentI].high = tree[nodeI].high;
	tree[parentI].val = tree[nodeI].val + tree[nodeI-1].val;
	nodeI = parentI;
	if(nodeI == 0)
	  break; // root
      }
    } // FORI

    // Handle queries:
    string s;
    bool done = false;
    while(!done) {
      cin >> s;
      switch(s[0]) {
      case 'S': // Update tree:
	{
	  int i; cin >> i; --i;
	  int nodeI = rowIdx + i;
	  int oldVal = tree[nodeI].val;
	  cin >> tree[nodeI].val;
	  int diff = tree[nodeI].val - oldVal;
	  // Bump data up:
	  while(true) {
	    int parentI = (nodeI-1)/2;
	    tree[parentI].val += diff;
	    nodeI = parentI;
	    if(nodeI == 0)
	      break; // root
	  }
	}
	break;
      case 'M':
	{
	  int low, high; cin >> low >> high; --low; --high;
	  cout << read(low, high, 0) << endl;
	}
	break;
      case 'E':
	done = true;
	break;
      default:
	die();
      }
    }

    delete[] tree;
  }
}
