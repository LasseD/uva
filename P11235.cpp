/*
  Represents interval including low and high
*/
struct Node {
  int low, high, val;
  void set(int l, int h, int v) {
    low = l; high = h; val = v;
  }
};

int freq(int reqLow, int reqHigh, Node const * const tree, int idx) {
  const Node &n = tree[idx];
  if(reqHigh < n.low || reqLow > n.high) {
    return 0;
  }
  if(reqLow <= n.low && n.high <= reqHigh) {
    return n.val;
  }
  if(n.val == n.high - n.low + 1) { // Is leaf
    if(n.low < reqLow) {
      //cerr << "# n.high=" << n.high << ", reqLow=" << reqLow << " ";
      return MIN(n.high,reqHigh) - reqLow + 1;
    }
    if(n.high > reqHigh) {
      //cerr << "!";
      return reqHigh - MAX(n.low,reqLow) + 1;
    }
    //cerr << "?";
    return reqHigh - reqLow + 1;
  }
  int left = freq(reqLow, reqHigh, tree, idx*2+1);
  int right = freq(reqLow, reqHigh, tree, idx*2+2);
  return MAX(left, right);
}

int main() {
  int n, q, a[100009], x;
  while(true) {
    cin >> n;
    if(n == 0)
      return 0;
    cin >> q;
    int prev = -99999999;
    int leafs = 0;
    FORI(n) {
      cin >> x;
      if(x != prev) {
	a[leafs++] = 1;
	prev = x;
      }
      else {
	++a[leafs-1];
      }
    } // FORI(n)

    Node *tree = new Node[4*leafs];
    int height = 1;
    int rowSize = 1;
    int rowI = 0;
    while(rowSize < leafs) {
      ++height;
      rowI += rowSize;
      rowSize <<= 1;
    }
    // Build tree:
    int low = 0; // Left side
    FORI(rowSize) {
      int size = i >= leafs ? 0 : a[i];
      tree[rowI+i].set(low, low+size-1, size);
      low += size; // Full Binary tree
      // Bubble up:
      int idx = rowI+i;
      while(idx > 0) { // While not at the root
	int parentI = (idx-1)/2;
	if(idx != parentI*2+2)
	  break; // Not a right child.
	int val = MAX(tree[idx-1].val, tree[idx].val);
	//cerr << "Setting " << parentI << " ";
	tree[parentI].set(tree[idx-1].low, tree[idx].high, val);
	idx = parentI;
      }
    }
    
    FORI(q) {
      int low, high;
      cin >> low >> high; --low; --high;
      int ret = freq(low, high, tree, 0);
      if(ret == 0)
	ret = 1;
      cout << ret << endl;
    }

    delete[] tree;
  } // while(true)
} // int main
