int main() {
  vector<int> dances[1001];
  int GNumbers[1001];
  FORCAS {
    if(cas != 0)
      cout << endl;
    int D, P, d1, d2;
    cin >> P >> D; // P persons, D dances
    FORI(P)
      dances[i].clear();
    memset(GNumbers, -1, P*sizeof(int));    
    GNumbers[0] = 0;

    FORI(D) {
      cin >> d1 >> d2;
      dances[d1].push_back(d2);
      dances[d2].push_back(d1);
    }

    // Push waves:
    vector<int> v;
    v.push_back(0);
    int GNumber = 0;
    while(!v.empty()) {
      ++GNumber;
      vector<int> w;
      FORIT(vector<int>, v) {
	int e = *it;	
	FORIT2(vector<int>, dances[e]) {
	  int e2 = *it2;
	  if(GNumbers[e2] != -1)
	    continue; // already seen.
	  GNumbers[e2] = GNumber;
	  w.push_back(e2);
	} // FORIT2
      } // FORIT
      v = w;
    } // while(!v.empty())
    FORI(P-1)
      cout << GNumbers[i+1] << endl;

  } // FORCAS
  return 0;
}
