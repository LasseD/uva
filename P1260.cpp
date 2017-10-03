/*
Binary tree:
     0
  1     2
3   4 5   6
So children are 2*n+1 and 2*n+2
 */
int main() {
  int n, a[1001], tree[2048], indices[1001];
  PI valToI[1001];
  FORCAS {
    cin >> n;
    FORI(n) {
      cin >> a[i];
      valToI[i] = PI(a[i], i);
    }
    sort(valToI, valToI+n);
    FORI(n)
      indices[valToI[i].second] = i; // Index in leafs of binary tree.

    // Build binary tree to be used to find output:
    memset(tree, 0, sizeof(tree));
    int height = 0;
    int startLeafs = 0;
    int numLeafs = 1;
    while(numLeafs < n) {
      height++;
      startLeafs += numLeafs;
      numLeafs <<= 1;
    }
    // Let the nodes in the tree contain the size of the subtrees.
    int ret = 0;
    FORI(n) {
      int valI = startLeafs + indices[i];
      // Find number of sales less than or equal to val:
      while(valI != 0) { // Walk up until root:
	int parent = (valI-1)>>1;
	bool isLeft = valI == (parent<<1)+1;
	if(!isLeft) {
	  ret += tree[parent] - tree[valI];
	}
	++tree[valI]; // Update tree
	valI = parent;
      }
      ++tree[0]; // Update tree
    }
    cout << ret << endl;
  }
  return 0;
}
