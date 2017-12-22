int main() {
  int cntB[61], cntS[61];
  for(int cas = 1; true; ++cas) {
    // Reset and read data:
    GI(B); GI(S); if(B == 0 && S == 0) return 0;
    memset(cntB, 0, sizeof(cntB));
    memset(cntS, 0, sizeof(cntS));
    FORI(B) {
      GI(b);
      ++cntB[b];
    }
    FORI(S) {
      GI(s);
      ++cntS[s];
    }

    // Run:
    for(int b = 60; b >= 2; --b) {
      while(cntB[b] > 0) {
	// Reduce:
	int nearestS = -1000;
	for(int s = 2; s <= 60; ++s) {
	  if(cntS[s] > 0 && ABS(b-s) < ABS(b-nearestS))
	    nearestS = s;
	}
	if(nearestS == -1000)
	  break;
	int pairs = min(cntB[b], cntS[nearestS]);
	cntB[b] -= pairs;
	cntS[nearestS] -= pairs;	
      }
    }
    // Output:
    int oldestB = -1;
    LL left = 0;
    for(int b = 60; b >= 2; --b) {
      if(cntB[b] > 0) {
	oldestB = b;
      }
      left += cntB[b];
    }
    cout << "Case " << cas << ": " << left;
    if(oldestB != -1)
      cout << " " << oldestB;
    cout << endl;
  }
}
