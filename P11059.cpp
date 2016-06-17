#include <iostream>

typedef long long ll;

void updateMax(ll &max, const ll allProd, const ll afn, const ll bln, const bool evenNegs) {
  //std::cerr << "Updating max: max=" << max << ", allProd=" << allProd << ", afn=" << afn << ", bln=" << bln << ", evenNegs=" << evenNegs << std::endl;
  if(evenNegs) {
    if(allProd > max)
      max = allProd;
    return;
  }
  
  // Uneven negs: Max is either allProd/bfn or allProd/aln
  if(afn > max)
    max = afn;
  if(bln > max)
    max = bln;
}

int main() {
  int N, a;
  for(int cas = 1; std::cin >> N; ++cas) {
    ll max = 0;
    ll allProd = 0;
    ll afterFirstNeg = 0;
    ll beforeLastNeg = 0;
    bool evenNegs = true;
    bool anyNegs = false;
    for(int i = 0; i < N; ++i) {
      std::cin >> a;
      if(a == 0) {
	updateMax(max, allProd, afterFirstNeg, beforeLastNeg, evenNegs);
	allProd = 0;
	afterFirstNeg = 0;
	beforeLastNeg = 0;
	anyNegs = false;
	evenNegs = true;
      }
      else if(a > 0) {
	if(allProd == 0)
	  allProd = a;
	else
	  allProd *= a;
	if(anyNegs) {
	  if(afterFirstNeg == 0)
	    afterFirstNeg = a;
	  else
	    afterFirstNeg *= a;
	}
      }
      else { // a < 0:
	beforeLastNeg = allProd;
	if(allProd == 0)
	  allProd = -a;
	else
	  allProd *= -a;
	if(anyNegs) {
	  if(afterFirstNeg == 0)
	    afterFirstNeg = -a;
	  else
	    afterFirstNeg *= -a;
	}
	evenNegs = !evenNegs;
	anyNegs = true;
      }
    }
    updateMax(max, allProd, afterFirstNeg, beforeLastNeg, evenNegs);
    std::cout << "Case #" << cas << ": The maximum product is " << max << "." << std::endl << std::endl;
  }
}
