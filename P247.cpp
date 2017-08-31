int main() {
  bool M[25][25];
  int n; // Max 25.
  int m; // Edges
  bool printed[25];

  for(int cas = 1; true; ++cas) {
    cin >> n >> m;
    if(n == 0 && m == 0)
      return 0;
    // Read input:
    string a, b;
    int x, y;
    map<string,int> names;
    map<int,string> rnames;
    FORI(n) {
      printed[i] = false;
      FORJ(n)
	M[i][j] = false;
    }
    FORI(m) {
      cin >> a >> b;
      if(names.find(a) == names.end()) {
	int sz = (int)names.size();
	rnames[sz] = a;
	names[a] = sz;
      }
      if(names.find(b) == names.end()) {
	int sz = (int)names.size();
	rnames[sz] = b;
	names[b] = sz;
      }
      x = names[a];
      y = names[b];
      M[x][y] = true;
    }

    // Compute calling circles:
    bool improved = true;
    while(improved) {
      improved = false;
      FORI(n) {
	FORJ(n) {
	  if(j == i)
	    continue;
	  if(M[i][j])
	    continue; // Link already OK.
	  FORK(n) {
	    if(k == i || k == j)
	      continue;
	    if(M[i][k] && M[k][j]) {
	      improved = true;
	      M[i][j] = true;
	      break; // Breaks from FORK.
	    }
	  } // FORK
	} // FORJ
      } // FORI
    } // while(improved)

    // Output:
    if(cas != 1)
      cout << endl;
    cout << "Calling circles for data set " << cas << ":" << endl;
    FORI(n) {
      if(printed[i])
	continue;
      printed[i] = true;
      cout << rnames[i];
      FORJ(n) {
	if(i == j || printed[j])
	  continue;
	if(M[i][j] && M[j][i]) {
	  cout << ", " << rnames[j];
	  printed[j] = true;
	}
      }
      cout << endl;
    }
  }
  return 0;  
}
