#include <iostream>
#include <stdio.h>
#include <vector>

/*
 Binary tree: Sequence of (n,s): n: value, s: L/R path
 */
//typedef unsigned int Node;
struct Node {
  unsigned int value;
  Node *L;
  Node *R;
};

#define TREE_SIZE 256

bool checkTree(Node const * const node) {
  if(node == NULL)
    return true;
  if(node->value == 0)
    return false;
  if(!checkTree(node->L))
    return false;
  if(!checkTree(node->R))
    return false;
  return true;
}

void printTree(Node * node) {
  std::vector<Node* > lv;

  lv.push_back(node);

  while(!lv.empty()) {
    // Print all in lv
    std::vector<Node* > nxt;
    for(std::vector<Node*>::iterator it = lv.begin(); it != lv.end(); ++it) {
      Node *n = *it;
      if(n != node)
	std::cout << " ";
      std::cout << n->value;
      if(n->L != NULL)
	nxt.push_back(n->L);
      if(n->R != NULL)
	nxt.push_back(n->R);      
    }
    lv = nxt;
  }
  std::cout << std::endl;
}

int main() {
  Node tree[TREE_SIZE];

  while(true) {
    // Reset tree:
    for(unsigned int i = 0; i < TREE_SIZE; ++i) {
      tree[i].value = 0;
      tree[i].L = NULL;
      tree[i].R = NULL;
    }
    unsigned int treeI = 1; // next node to construct.

    // Read from input and build tree
    unsigned int value;
    char path[256];
    bool error = false;

    // Read/construct loop:
    while(true) {
      // Read:
      std::cin >> path;
      if(std::cin.eof())
	return 0;

      if(path[1] == ')') {
	break; // case ()
      }

      // Build node:
      // Compute value:
      value = path[1]-'0';
      unsigned int i = 2;
      while(path[i] != ',') {
	value = value*10+(path[i]-'0');
	++i;
      }
      ++i;
      Node *node = &tree[0];
      // Compute path:
      while(path[i] != ')') {
	if(path[i] == 'R') {
	  if(node->R == NULL) {
	    node->R = &tree[treeI++];
	  }
	  node = node->R;
	}
	else {
	  if(node->L == NULL) {
	    node->L = &tree[treeI++];
	  }
	  node = node->L;
	}
	++i;
      }
      // Set value at current location:
      if(node->value != 0) {
	error = true;
        //std::cerr << "Doubly specified node " << path << " value: " << value << std::endl;
      }
      //std::cerr << "Added node " << path << " value: " << value << std::endl;
      node->value = value; // normal case
    } // end read/construct.

    //std::cerr << "Done reading" << std::endl;
    // Check tree:
    Node *node = &tree[0];
    if(error || !checkTree(node)) {
      std::cout << "not complete" << std::endl;
      continue;
    }
      
    printTree(node);

  }
}
