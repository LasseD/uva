#include <iostream>
#include <map>

typedef std::map<int,int> Map;

int main() {
  int NC, a, b, A, M[900];
  int cas = 1;
  while(true) {
    std::cin >> NC;
    if(NC == 0)
      return 0;
    Map m;
    for(int i = 0; i < 900; ++i)
      M[i] = 99999;
    for(int i = 0; i < NC; ++i) {
      std::cin >> a >> b;
      if(m.find(a) == m.end())
	m.insert(std::make_pair(a, m.size()));
      if(m.find(b) == m.end())
	m.insert(std::make_pair(b, m.size()));
      a = m[a];
      b = m[b];
      M[a*30+b] = M[b*30+a] = 1;      
    }
    int size = (int)m.size();

    // Compute graph:
    bool anyImprovements = true;
    while(anyImprovements) {
      anyImprovements = false;
      // Iterate matrix:
      for(int i = 0; i < size; ++i) {
	for(int j = i+1; j < size; ++j) {
	  for(int k = 0; k < size; ++k) {
	    if(k == i || k == j)
	      continue;
	    if(M[i*30+j] > M[i*30+k]+M[k*30+j]) {
	      anyImprovements = true;
	      M[i*30+j] = M[j*30+i] = M[i*30+k]+M[k*30+j];
	    }
	  } // for k
	} // for j
      } // for i
    } // while anyImprovements

    /*
    for(Map::const_iterator it1 = m.begin(); it1 != m.end(); ++it1) {
      for(Map::const_iterator it2 = m.find(it1->first); it2 != m.end(); ++it2) {
	if(M[it1->second*30+it2->second] < 99999)
	  std::cerr << it1->first << "->" << it2->first << ": " << M[it1->second*30+it2->second] << std::endl;
      }
    }//*/

    while(true) {
      std::cin >> A >> b;
      if(A == 0 && b == 0)
	break;
      a = m[A];

      int unreachable = 0;
      for(int i = 0; i < size; ++i) {
	if(i == a)
	  continue;
	if(M[i*30+a] > b)
	  ++unreachable;
      }
      std::cout << "Case " << (cas++) << ": " << unreachable << " nodes not reachable from node " << A << " with TTL = " << b << "." << std::endl;
    } // while true
  } // while true
}
