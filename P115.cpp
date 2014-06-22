#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <set>
#include <map>
#include <stack>

#define TREE_SIZE 400

struct Node {
  Node *p1;
  Node *p2;
  std::string name;
  int i;  
};

int relate(Node *up, Node *down) {
  //std::cerr << "checking parenthood " << up->name << " and " << down->name << std::endl;
  std::stack<Node*> ancestors;  
  down->i = 0;
  ancestors.push(down);
  
  while(!ancestors.empty()) {
    Node *ancestor = ancestors.top();
    ancestors.pop();
    if(ancestor == up)
      return ancestor->i;

    if(ancestor->p1 != NULL) {
      ancestor->p1->i = ancestor->i+1;
      ancestors.push(ancestor->p1);
    }
    if(ancestor->p2 != NULL) {
      ancestor->p2->i = ancestor->i+1;
      ancestors.push(ancestor->p2);
    }
  }
  return 0;
}

void paintAncestors(Node *m) {
  //std::cerr << "Painting ancestors of '" << m->name << "'" << std::endl;
  std::stack<Node*> todo;
  m->i = 0;
  todo.push(m);
  
  while(!todo.empty()) {
    Node *n = todo.top();
    todo.pop();
    if(n->p1 != NULL) {
      n->p1->i = n->i+1;
      todo.push(n->p1);
    }
    if(n->p2 != NULL) {
      n->p2->i = n->i+1;
      todo.push(n->p2);
    }      
  }  
}

bool cousins(Node * const node, int &_n, int &_m) {
  //std::cerr << "checking cousins in painted tree for " << node->name << std::endl;

  std::stack<Node*> todo;
  node->i = 0;
  todo.push(node);

  Node *lca = NULL;
  int otherI;
  
  while(!todo.empty()) {
    Node *n = todo.top();
    todo.pop();
    if(n->p1 != NULL) {
      if(n->p1->i != -1) {
	// Common ancestor!
	if(lca == NULL || lca->i > n->p1->i) {
	  lca = n->p1;
	  otherI = n->i+1;
	}
	continue; // don't insert.
      }
      n->p1->i = n->i+1;
      todo.push(n->p1);
    }
    if(n->p2 != NULL) {
      if(n->p2->i != -1) {
	// Common ancestor!
	if(lca == NULL || lca->i > n->p2->i) {
	  lca = n->p2;
	  otherI = n->i+1;
	}
	continue; // don't insert.
      }
      n->p2->i = n->i+1;
      todo.push(n->p2);
    }      
  }  

  if(lca == NULL)
    return 0;

  // Fill ancestor sets:
  //std::cerr << "Found they are cousins! lca->i: " << lca->i << ", otherI: " << otherI << std::endl;

  lca->i--;
  otherI--;
  _n = std::min(lca->i, otherI);
  _m = lca->i - otherI;
  if(_m < 0)
    _m = -_m;
}

int main() {
  // Load tree:
  Node tree[TREE_SIZE];
  int treeI = 0;
  std::map<std::string, Node*> map;

  char line[256];
  while(true) {
    std::cin.getline(line, 256);
    int start1 = -1;
    int start2 = -1;
    for(int i = 0; i < 256; ++i) {
      if(line[i] == ' ')
	line[i] = '\0';
      else if(line[i] == '\n' || line[i] == '\r') {
	line[i] = '\0';
	break;
      }
      else if(start1 == -1)
	start1 = i;
      else if(start2 == -1 && line[i-1] == '\0')
	start2 = i;
    }
    if(start1 == -1 || start2==-1)
      throw std::exception();
    std::string child(&line[start1]);
    std::string parent(&line[start2]);

    if(child == "no.child")
      break;

    // handle parent:
    std::map<std::string, Node*>::const_iterator it = map.find(parent);
    Node* p;
    if(it == map.end()) {
      p = &tree[treeI++];
      p->p1 = p->p2 = NULL;
      p->name = parent;
      map.insert(std::make_pair(parent, p));
      //std::cerr << "NEW PARENT: '" << parent << "'" << std::endl;
    }
    else {
      p = it->second;
    }    
    
    // handle child:
    it = map.find(child);
    if(it != map.end()) {
      //std::cerr << "CHILD SEEN BEFORE: '" << child << "'" << std::endl;
      Node *c = it->second;
      if(c->p1 == NULL)
	c->p1 = p;
      else if(c->p2 == NULL)
	c->p2 = p;
      else
	throw std::exception();
    }
    else {
      //std::cerr << "NEW CHILD: '" << child << "'" << std::endl;
      // handle child:
      Node *c = &tree[treeI++];
      c->name = child;
      c->p1 = p;
      c->p2 = NULL;
      map.insert(std::make_pair(child, c));
    }
  }
  //std::cerr << "Read " << treeI << " relationships." << std::endl;

  // Handle queries:
  while(std::cin.getline(line, 256)) {
    int start1 = -1;
    int start2 = -1;
    for(int i = 0; i < 256; ++i) {
      if(line[i] == ' ')
	line[i] = '\0';
      else if(line[i] == '\n' || line[i] == '\r') {
	line[i] = '\0';
	break;
      }
      else if(start1 == -1)
	start1 = i;
      else if(start2 == -1 && line[i-1] == '\0')
	start2 = i;
    }
    std::string p1(&line[start1]);
    std::string p2(&line[start2]);
    if(start1 == -1 || start2==-1)
      throw std::exception();

    //    if(p1 == "no.child")
    //      throw std::exception();

    std::map<std::string, Node*>::const_iterator it1 = map.find(p1);
    std::map<std::string, Node*>::const_iterator it2 = map.find(p2);
    if(it1 == map.end() || it2 == map.end()) {
      std::cout << "no relation" << std::endl;       
      continue;
    }

    if(p1 == p2) {
      std::cout << "child" << std::endl; // should be sibling
      continue;
    }

    Node* n1 = it1->second;
    Node* n2 = it2->second;

    if(n1->p1 == n2->p1 && n1->p1 != NULL || 
       n1->p2 == n2->p2 && n1->p2 != NULL || 
       n1->p2 == n2->p1 && n1->p2 != NULL || 
       n1->p1 == n2->p2 && n1->p1 != NULL) {
      std::cout << "sibling" << std::endl;
      continue;
    }
    int n;
    if((n = relate(n1, n2)) != 0) {
      if(n == 1)
	std::cout << "parent" << std::endl;
      else {
	for(int i = 2; i < n; ++i) {
	  std::cout << "great ";
	}
	std::cout << "grand parent" << std::endl;
      }
      continue;
    }
    if((n = relate(n2, n1)) != 0) {
      if(n == 1)
	std::cout << "child" << std::endl;
      else {
	for(int i = 2; i < n; ++i) {
	  std::cout << "great ";
	}
	std::cout << "grand child" << std::endl;
      }      
      continue;
    }
    // OK. Bring out the big guns. Set the i of the tree to -1:
    for(int i = 0; i < TREE_SIZE; ++i) {
      tree[i].i = -1;
    }
    paintAncestors(n1);
    
    int m;
    if(cousins(n2, n, m)) {
      
      {
	for(int i = 0; i < TREE_SIZE; ++i) {
	  tree[i].i = -1;
	}
	paintAncestors(n2);
	int _n, _m;
	cousins(n1, _n, _m);
	if(_n < n) {
	  n = _n;
	  m = _m;
	}
      }

      std::cout << n << " cousin";
      if(m != 0)
	std::cout << " removed " << m << std::endl;
      else
	std::cout << std::endl;	
    }
    else {
      std::cout << "no relation" << std::endl;      
    }
  }
  return 0;
}
