#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <stack>

typedef std::pair<int,int> PP;

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return ret;
}

bool readEdge(PP &edge) {
  char w[10];
  if(!gets(w) || w[0] < 'A' || w[0] > 'Z')
    return false;
  edge.first = w[0]-'A';
  edge.second = w[1]-'A';
  return true;
}

int main() {
  char line[10];

  int citizens[26]; // citizen -> edge index.
  PP edges[1000];

  unsigned int cases = readUInt();
  gets(line); // Empty line
  
  for(unsigned int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    // Read number of citizens:
    gets(line);
    int N = line[0]-'A'+1; //number of citizens.
    for(int i = 0; i < N; ++i)
      citizens[i] = -2;
    //std::cerr << "Citizens: " << N << std::endl;

    // Read edges:
    PP edge;
    int M = 0;
    for(; readEdge(edge); ++M) {
      if(edge.first == edge.second)
	continue;
      edges[2*M] = edge;
      std::swap(edge.first, edge.second);
      edges[2*M+1] = edge;
    }
    std::sort(edges, edges+2*M);
    int prev = -1;
    for(int i = 0; i < 2*M; ++i) {
      if(edges[i].first != prev) {
	prev = edges[i].first;
	citizens[prev] = i;
      }
    }
    //std::cerr << "Edges: " << M << std::endl;
    
    // Compute connected components:
    int components = 0;
    std::stack<int> s;
    for(int i = 0; i < N; ++i) {
      if(citizens[i] == -1)
	continue; // Already handled.
      ++components;
      if(citizens[i] == -2) {
	continue; // No edges.
      }
      s.push(i);
      while(!s.empty()) {
	int citizen = s.top();
	s.pop();
	if(citizens[citizen] == -1)
	  continue; // Already handled.
	for(int j = citizens[citizen]; edges[j].first == citizen; ++j) {
	  s.push(edges[j].second);
	}
	citizens[citizen] = -1;
      } // while(!s.empty)
    } // for i
    std::cout << components << std::endl;
  } // for case

  return 0;
}
