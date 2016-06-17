#include <iostream>
#include <stdio.h>
#include <set>

typedef std::set<int> Set;

int main() {
  int a, b, mtx[100*100], vertices[100], numVertices; // index a*100+b -> clicks from a to b.
  for(int cas = 1; true; ++cas) {
    // Read graph:
    Set s;
    for(int i = 0; i < 100*100; ++i)
      mtx[i] = 1000; // Larger than possible max.
    while(true) {
      std::cin >> a >> b;
      if(a == 0 && b == 0)
	break;
      --a;
      --b;
      mtx[a*100+b] = 1;
      if(s.find(a) == s.end())
	s.insert(a);
      if(s.find(b) == s.end())
	s.insert(b);
    }
    if(s.empty())
      return 0;
    numVertices = 0;
    for(Set::const_iterator it = s.begin(); it != s.end(); ++it) {
      vertices[numVertices++] = *it;
    }
    
    // Run relaxation:
    bool improved = true;
    while(improved) {
      improved = false;
      // Try to find x->y->z improvements:
      for(int xI = 0; xI < numVertices; ++xI) {
	int x = vertices[xI];
	for(int yI = 0; yI < numVertices; ++yI) {
	  if(xI == yI)
	    continue;
	  int y = vertices[yI];
	  for(int zI = 0; zI < numVertices; ++zI) {
	    if(xI == zI || yI == zI)
	      continue;
	    int z = vertices[zI];
	    int &stepsXZ = mtx[x*100+z];
	    int stepsOverY = mtx[x*100+y]+mtx[y*100+z];
	    if(stepsOverY < stepsXZ) {
	      improved = true;
	      stepsXZ = stepsOverY;
	    }	      
	  }	  
	}	
      }
    }

    // Find and print result:
    long numberOfPaths = numVertices*(numVertices-1);
    long sum = 0;
    for(int xI = 0; xI < numVertices; ++xI) {
      int x = vertices[xI];
      for(int yI = 0; yI < numVertices; ++yI) {
	if(xI == yI)
	  continue;
	int y = vertices[yI];
	sum += mtx[x*100+y];
	//std::cerr << (x+1) << "->" << (y+1) << ": " << mtx[x*100+y] << std::endl;
      }
    }
    printf("Case %d: average length between pages = %.3f clicks\n", cas, sum/(double)numberOfPaths);
  }
}
