int main() {
  bool H[10][10], V[10][10];
  int n, m, I, J;
  string s;
  for(int cas = 0; cin >> n >> m; ++cas) {
    if(cas != 0)
      cout << endl << "**********************************" << endl << endl;
    cout << "Problem #" << cas+1 << endl << endl;
    FORY(n) {
      FORX(n) {
	H[y][x] = V[y][x] = false;
      }
    }
    FORI(m) {
      cin >> s >> I >> J; --I; --J;
      if(s[0] == 'V') {
	H[I][J] = true;
      }
      else {
	V[J][I] = true;
      }
    }
    // Debug:
    /*
    FORY(n) {
      FORX(n-1) {
	if(H[y][x])
	  cerr << ".-";
	else
	  cerr << ". ";
      }
      cerr << "." << endl;
      if(y < n) {
	FORX(n) {
	  if(V[y][x])
	    cerr << "| ";
	  else
	    cerr << "  ";
	}
      }
      cerr << endl;
    }//*/

    // Find all:
    bool any = false;
    for(int size = 1; size < n; ++size) {
      int cnt = 0;
      for(int y0 = 0; y0+size < n; ++y0) {
	for(int x0 = 0; x0+size < n; ++x0) {
	  // Can I make the square:
	  bool ok = true;
	  FORI(size && ok) {
	    ok = H[y0][i+x0];
	  }
	  FORI(size && ok) {
	    ok = H[y0+size][i+x0];
	  }
	  FORI(size && ok) {
	    ok = V[y0+i][x0];
	  }
	  FORI(size && ok) {
	    ok = V[y0+i][x0+size];
	  }
	  if(ok) {
	    ++cnt;
	  }
	} // x0
      } // y0
      if(cnt > 0) {
	any = true;
	cout << cnt << " square (s) of size " << size << endl;    
      }
    } // size
    if(!any)
      cout << "No completed squares can be found." << endl;
  }
  return 0; 
}
