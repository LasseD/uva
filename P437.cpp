#include <iostream>
#include <cstring>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))

typedef std::pair<int,int> PP;

std::ostream& operator<<(std::ostream& os, const PP& p) {
  os << "(" << p.first << "," << p.second << ")";
  return os;
}

// n <= 30 => 90 types of bases. 
int main() {
  int n, a, b, c;
  PP bases[90];
  int heights[90*90]; // index x*90+y => height for base index x to base index y
  for(int cas = 1; true; ++cas) {
    // Read and set up:
    int max = 0;
    std::cin >> n;
    if(n == 0)
      return 0;
    for(int i = 0; i < 3*n; ++i)
      for(int j = 0; j < 3*n; ++j)
	heights[i*90+j] = 0;
    //memset(heights, 0, 90*90);
    for(int i = 0; i < n; ++i) {
      std::cin >> a >> b >> c;
      max = MAX(max,MAX(a,MAX(b,c)));
      int idx1 = 3*i;
      int idx2 = 3*i+1;
      int idx3 = 3*i+2;
      bases[idx1] = PP(MIN(a,b), MAX(a,b));
      bases[idx2] = PP(MIN(b,c), MAX(b,c));
      bases[idx3] = PP(MIN(a,c), MAX(a,c));
      heights[idx1*90+idx1] = c;
      heights[idx2*90+idx2] = a;
      heights[idx3*90+idx3] = b;
    }
    bool improved = true;
    while(improved) {
      improved = false;
      // Try to make improvement:
      for(int baseI = 0; baseI < 3*n; ++baseI) {
	PP base = bases[baseI];
	int baseHeight = heights[90*baseI+baseI];
	//std::cerr << "Try base " << baseI << ": " << base << " height " << baseHeight << std::endl;
	// Try to put the tower of base on top of a foundation from base a to b:
	for(int b = 0; b < 3*n; ++b) {
	  PP baseB = bases[b];
	  if(baseB.first <= base.first || baseB.second <= base.second)
	    continue;

	  for(int a = 0; a < 3*n; ++a) {
	    PP baseA = bases[a];
	    if(!(baseA.first == baseB.first || baseA.second == baseB.second) && (baseA.first <= baseB.first || baseA.second <= baseB.second))
	      continue;
	    if(heights[a*90+b] + baseHeight > heights[a*90+baseI]) {
	      heights[a*90+baseI] = heights[a*90+b] + baseHeight;
	      //std::cerr << "Combine " << bases[a] << "->" << bases[b] << " height " << heights[a*90+b] << " with base " << base << " height " << baseHeight << std::endl;
	      improved = true;
	      max = MAX(max, heights[a*90+baseI]);
	    }
	  }
	}
      }
    }
    std::cout << "Case " << cas << ": maximum height = " << max << std::endl;
  }
}
