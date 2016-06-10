#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <sstream>

typedef std::string String;

/*
Finds if a node is critical by visiting all nodes connected to one of the neighbours. If all other neighbours are visited, then the node is not critical.
 */
bool isCritical(int nodeIndex, std::vector<int> *E, int N) {
  bool visited[100];
  for(int i = 0; i < N; ++i)
    visited[i] = false;
  visited[nodeIndex] = true;

  if(E[nodeIndex].size() < 2)
    return false; // Not critical if alone or only with one neighbour.

  // Visit all that are connected to the first neighbour:
  std::stack<int> s;
  s.push(E[nodeIndex][0]);
  while(!s.empty()) {
    int curr = s.top();
    s.pop();
    if(visited[curr])
      continue;
    visited[curr] = true;
    for(std::vector<int>::const_iterator it = E[curr].begin(); it != E[curr].end(); ++it) {
      if(visited[*it])
	continue;
      s.push(*it);
    }    
  }
  
  for(std::vector<int>::const_iterator it = E[nodeIndex].begin(); it != E[nodeIndex].end(); ++it) {
    if(!visited[*it])
      return true; // unvisited neighbout.
  }
  return false;
}

int main() {
  String w;

  std::vector<int> E[100];
  int N, n1, n2;
  
  while(true) {
    std::stringstream ss1;
    std::getline(std::cin,w); ss1 << w; ss1 >> N;
    if(N == 0)
      return 0;
    //std::cerr << "Graph of size " << N << std::endl;

    for(int i = 0; i < N; ++i)
      E[i].clear();

    while(true) {
      std::stringstream ss2;
      std::getline(std::cin,w); ss2 << w; ss2 >> n1; 
      if(n1 == 0)
	break;
      --n1;
      while(ss2 >> n2) {
	--n2;
	E[n1].push_back(n2);
	E[n2].push_back(n1);
      }      
    }
    
    int critical = 0;
    for(int i = 0; i < N; ++i) {
      if(isCritical(i, E, N))
	++critical;
    }
    std::cout << critical << std::endl;
  }  
}
