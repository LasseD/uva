#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <set>
#include <map>
#include <stack>
#include <stdexcept>

#define TREE_SIZE 800

struct Node {
  Node *p;
};

int relate(Node *up, Node *down) {
  int i = 0;
  Node* n = down;
  while(n != NULL) {
    if(n == up)
      return i;
    n = n->p;
    ++i;
  }
  return 0;
}

bool cousins(Node * const n1, Node * const n2, int &_n, int &_m) {
  std::stack<Node*> s1;
  Node *_n1 = n1;
  while(_n1 != NULL) {
    s1.push(_n1);
    _n1 = _n1->p;
  }

  std::stack<Node*> s2;  
  Node *_n2 = n2;
  while(_n2 != NULL) {
    s2.push(_n2);
    _n2 = _n2->p;
  }

  if(s1.top() != s2.top())
    return false;

  while(s1.top() == s2.top()) {
    s1.pop();
    s2.pop();
  }

  _n = std::min(s1.size(), s2.size())-1;
  _m = s1.size() - s2.size();
  if(_m < 0)
    _m = -_m;
  return true;
}

int main() {
  // Load tree:
  Node tree[TREE_SIZE];
  int treeI = 0;
  std::map<std::string, Node*> map;

  std::string parent, child, p1, p2;
  while(true) {
    std::cin >> child >> parent;

    if(child == "no.child")
      break;

    // handle parent:
    std::map<std::string, Node*>::const_iterator it = map.find(parent);
    Node* p;
    if(it == map.end()) {
      p = &tree[treeI++];
      p->p = NULL;
      map.insert(std::make_pair(parent, p));
    }
    else {
      p = it->second;
    }    
    
    // handle child:
    it = map.find(child);
    if(it != map.end()) {
      Node* c = it->second;
      if(c->p != NULL && c->p != p) {
        throw std::runtime_error("child seen before");
      }
      c->p = p;
    }
    else {
      // handle child:
      Node *c = &tree[treeI++];
      c->p = p;
      map.insert(std::make_pair(child, c));
    }
  }

  // Handle queries:
  while(std::cin >> p1 >> p2) {
    std::map<std::string, Node*>::const_iterator it1 = map.find(p1);
    std::map<std::string, Node*>::const_iterator it2 = map.find(p2);
    if(it1 == map.end() || it2 == map.end()) {
      std::cout << "no relation" << std::endl;       
      continue;
    }

    if(p1 == p2) {
      throw std::runtime_error("malformed query a, a: " + p1);
    }

    Node* n1 = it1->second;
    Node* n2 = it2->second;
    int n, m;

    if(n1->p == n2->p && n1->p != NULL) {
      std::cout << "sibling" << std::endl;
    }
    else if((n = relate(n1, n2)) != 0) {
      if(n == 1)
	std::cout << "parent" << std::endl;
      else {
	for(int i = 2; i < n; ++i) {
	  std::cout << "great ";
	}
	std::cout << "grand parent" << std::endl;
      }
    }
    else if((n = relate(n2, n1)) != 0) {
      if(n == 1)
	std::cout << "child" << std::endl;
      else {
	for(int i = 2; i < n; ++i) {
	  std::cout << "great ";
	}
	std::cout << "grand child" << std::endl;
      }      
    }
    else if(cousins(n1, n2, n, m)) {
      if(m != 0)
	std::cout << n << " cousin" << " removed " << m << std::endl;
      else
	std::cout << n << " cousin" << std::endl;	
    }
    else {
      std::cout << "no relation" << std::endl;      
    }
  }
  return 0;
}
