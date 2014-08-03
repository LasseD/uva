#include <iostream>
#include <vector>

/*
1: Paskill: Prolog interpreter - destroy programs, don't re-enter self visited, ++ walk
2: Lisper: Hello World - removes node, --walk
 */

struct Node {
  char c;
  bool markP, markL;
  std::vector<Node*> n;
};

int main() {
  Node nodes['Z'+1];
  for(char c = 'A'; c <= 'Z'; ++c)
    nodes[(int)c].c = c;

  std::string line;
  while(true) {
    getline(std::cin, line);
    if(line[0] == '#') {
      return 0;
    }
    //std::cerr << "Read: " << line << std::endl;
    // Clear graph:
    for(char c = 'A'; c <= 'Z'; ++c) {
      nodes[(int)c].n.clear();
      nodes[(int)c].markP = false;
      nodes[(int)c].markL = false;
    }
    // Construct graph:
    int i = 0;
    while(true) {
      char c = line[i++];
      char d;
      while(true) {
	d = line[++i];
	if(d == ';' || d == '.')
	  break;
	nodes[(int)c].n.push_back(&nodes[(int)d]);
	nodes[(int)d].n.push_back(&nodes[(int)c]);	
      }
      if(d == '.')
	break;
      ++i;
    }
    while(line[++i] == ' ')
      ;
    char paskill = line[i];
    nodes[(int)paskill].markP = true;
    while(line[++i] == ' ')
      ;
    char lisper = line[i++];
    nodes[(int)lisper].markL = true;
    // Simultate:

    bool ok = true;
    if(lisper == paskill) {
      std::cout << "Both annihilated in node " << lisper;
      ok = false;
    }
    while(ok) {
      {
	//std::cerr << "Paskill: " << paskill << ", Lisper: " << lisper << std::endl;
	// move paskill:
	char min = (char)127;
	char add = (char)127;
	for(std::vector<Node*>::const_iterator it = nodes[(int)paskill].n.begin(); it != nodes[(int)paskill].n.end(); ++it) {
	  Node *n = *it;
	  if(n->markL || n->markP)
	    continue;
	  //std::cerr << "Pakill neighbour " << n->c << std::endl;
	  if(n->c < min)
	    min = n->c;
	  if(n->c < add && n->c > nodes[(int)paskill].c)
	    add = n->c;
	}
	if(add != (char)127) {
	  paskill = add;
	  nodes[(int)paskill].markP = true;
	}
	else if(min != (char)127) {
	  paskill = min;
	  nodes[(int)paskill].markP = true;	
	}
	else {
	  std::cout << "Paskill trapped in node " << paskill;
	  ok = false;
	}
      }
      {
	// move lisper:
	char max = 0;
	char sub = 0;
	for(std::vector<Node*>::const_iterator it = nodes[(int)lisper].n.begin(); it != nodes[(int)lisper].n.end(); ++it) {
	  Node *n = *it;
	  if(n->markL)
	    continue;
	  if(n->c > max)
	    max = n->c;
	  if(n->c > sub && n->c < nodes[(int)lisper].c)
	    sub = n->c;
	}
	if(sub != 0) {
	  lisper = sub;
	  nodes[(int)lisper].markL = true;
	}
	else if(max != 0) {
	  lisper = max;
	  nodes[(int)lisper].markL = true;	
	}
	else {
	  if(!ok)
	    std::cout << " ";
	  std::cout << "Lisper trapped in node " << lisper;
	  ok = false;
	}

	if(lisper == paskill) {
	  if(!ok)
	    std::cout << " ";
	  std::cout << "Both annihilated in node " << lisper;
	  ok = false;
	}
	else if(nodes[(int)lisper].markP) {
	  if(!ok)
	    std::cout << " ";
	  std::cout << "Lisper destroyed in node " << lisper;
	  ok = false;
	}
      } // lisper
    } // while(true) - simulate
    std::cout << std::endl;
  } // while(true) - main
}
