#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define MIN(a,b) ((a) < (b) ? (a) : (b))

typedef pair<int,int> PP;
typedef long long ll;

int main() {
  int n, ele;
  while(true) {
    // Read input:
    cin >> n;
    if(n == 0)
      return 0;
    if(n == 1) {
      cin >> n; // Read the element
      cout << 0 << endl;
      continue;
    }
      
    PP *sortedElements = new PP[n]; // val, original index
    int *tree = new int[4*n]; // binary tree, elements contain sizes of sub trees.

    for(int i = 0; i < n; ++i) {
      cin >> ele;
      sortedElements[i] = PP(ele, i);
    }
    sort(sortedElements, sortedElements+n);
    // Build tree:
    int level = 0;
    int levelIndex = 0;
    int levelSize = 1;
    int elementSize = 1;
    while(elementSize < n)
      elementSize *= 2;

    tree[0] = n; // All elements under root.
    //cerr << "Tree sizes for n=" << n << ": " << endl << "(0)" << n << endl;
    while(levelSize < n) {
      ++level;
      levelIndex += levelSize;
      levelSize *= 2;
      elementSize /= 2;
      // Fill new level:      
      int rem = n;
      for(int i = 0; i < levelSize; ++i) {
	tree[levelIndex+i] = MIN(elementSize, rem);
	//cerr << "(" << (levelIndex+i) << ")" << tree[levelIndex+i] << " ";
	rem -= elementSize;
	if(rem < 0)
	  rem = 0;
      }
      //cerr << endl;
    }

    // Perform swaps:
    ll ret = 0;
    for(int i = 0; i < n; ++i) {
      //cerr << "Handling node " << sortedElements[i].first << " on sorted position " << i << ", original position: " << levelIndex << "+" << sortedElements[i].second << endl;
      // Count all left of element as swapped:
      int node = levelIndex + sortedElements[i].second;
      ll leftOfElement = 0;
      int parent = (node-1)/2;
      //int subTreeSize = 1; // The element itself
      while(node != 0) {
	bool isLeftChild = node == (parent*2+1); // right child would be parent*2+1.
	if(!isLeftChild) {
	  leftOfElement += tree[parent]-tree[node];
	  //cerr << "(" << node << ")" << tree[node] << " is right child of (" << parent << ")" << tree[parent] << ": + " << (tree[parent]-tree[node]) << endl;
	}
	//else cerr << "(" << node << ")" << tree[node] << " is left child of (" << parent << ")" << tree[parent] << endl;
	
	node = parent;
	parent = (node-1)/2;
      }
      //cerr << "Nodes to the left of " << node << ": " << leftOfElement << endl;
      ret += leftOfElement;
      
      // Remove element from tree:
      node = levelIndex + sortedElements[i].second;            
      while(node != 0) {
	--tree[node];
	node = (node-1)/2;
      } 
      --tree[0]; // Remember root.
    }
    cout << ret << endl;
    delete[] sortedElements;
    delete[] tree;
  }
}
