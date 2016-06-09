#include <iostream>
#include <stdio.h>

struct Node {
  Node *l, *r;
  char c;
};

void buildTree(Node *tree, int &numNodes, char *preorder, char *inorder, int len) {
  char root = preorder[0];
  int nodeIdx = numNodes;
  tree[nodeIdx].c = root;
  ++numNodes;

  int lenLeft = 0;
  char c;
  while((c = inorder[lenLeft]) != root)
    ++lenLeft;
  int lenRight = len - 1 - lenLeft;
  
  // Handle left child:
  if(lenLeft == 0) {
    tree[nodeIdx].l = NULL;
  }
  else {
    tree[nodeIdx].l = &tree[numNodes];
    buildTree(tree, numNodes, &preorder[1], inorder, lenLeft);
  }
  // Handle right child:
  if(lenRight == 0) {
    tree[nodeIdx].r = NULL;
  }
  else {
    tree[nodeIdx].r = &tree[numNodes];
    buildTree(tree, numNodes, &preorder[1+lenLeft], &inorder[1+lenLeft], lenRight);
  }  
}

void writePostOrder(Node *tree) {
  if(tree->l != NULL)
    writePostOrder(tree->l);
  if(tree->r != NULL)
    writePostOrder(tree->r);
  std::cout << tree->c;
}

int main() {
  char c, preorder[39], inorder[39];
  Node tree[39];

  while(std::cin >> preorder >> inorder) {
    // Reset tree:
    int numNodes = 0;
    int len = 0;
    while((c = preorder[len]) >= 'A' && c <= 'Z')
      ++len;
    buildTree(tree, numNodes, preorder, inorder, len);
    writePostOrder(tree);
    std::cout << std::endl;
  }
  return 0;
}
