struct Node {
  int cntNegs, cntZeros;
};

Node *tree;

// Return cntZeros, cntNegs
PI product(int nodeI) {
  PI ret;
  while(true) {
    int parentI = (nodeI-1)/2;
    if(nodeI == parentI*2+2) {
      // right child: Add info from left:
      ret.XX += tree[parentI*2+1].cntZeros;
      ret.YY += tree[parentI*2+1].cntNegs;
    }
    nodeI = parentI;
    if(nodeI == 0)
      break; // root
  }
  return ret;
}

int main() {
  tree = new Node[400000];
  
  int N, K;
  while(cin >> N >> K) {
    // Build tree:
    int rowSize = 1;
    int rowIdx = 0;
    while(rowSize <= N) {
      rowIdx += rowSize;
      rowSize <<= 1;
    }

    // Read data and set tree info:
    FORI(rowSize) { // Insert all leafs and bump data up the tree:
      int nodeI = rowIdx + i;
      if(i >= N)
	tree[nodeI].cntZeros = tree[nodeI].cntNegs = 0;
      else {
	GI(Z);
	tree[nodeI].cntZeros = Z == 0 ? 1 : 0;
	tree[nodeI].cntNegs = Z < 0 ? 1 : 0;
      }
      // Bump data up as long as we are at a right child:
      int parentI;
      while(((parentI = (nodeI-1)/2)*2+2) == nodeI) { // while we are the right child:
	tree[parentI].cntNegs = tree[nodeI].cntNegs + tree[nodeI-1].cntNegs;
	tree[parentI].cntZeros = tree[nodeI].cntZeros + tree[nodeI-1].cntZeros;
	nodeI = parentI;
	if(nodeI == 0)
	  break; // root
      }
    } // FORI

    // Handle queries:
    FORI(K) {
      GS(s); // command.
      if(s[0] == 'C') { // Change command:
	GI(nodeI); GI(V);
	nodeI = rowIdx + nodeI - 1;
	int negDiff = (V < 0 ? 1 : 0) - tree[nodeI].cntNegs;
	int zeroDiff = (V == 0 ? 1 : 0) - tree[nodeI].cntZeros;
	while(true) {
	  int parentI = (nodeI-1)/2;
	  tree[nodeI].cntZeros += zeroDiff;
	  tree[nodeI].cntNegs += negDiff;
	  nodeI = parentI;
	  if(nodeI == 0)
	    break; // root
	}
      }
      else { // P: Print command
	GI(low); GI(high);
	PI fromLow = product(rowIdx + low - 1);
	PI fromHigh = product(rowIdx + high);
	fromHigh.XX-=fromLow.XX;
	fromHigh.YY-=fromLow.YY;
	if(fromHigh.XX > 0)
	  cout << '0';
	else if(fromHigh.YY % 2 == 0)
	  cout << '+';
	else
	  cout << '-';
      }      
    }
    cout << endl;
  }
}
