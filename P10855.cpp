int main() {
  while(true) {
    GI(N); GI(n); if(N == 0 && n == 0) return 0;
    vector<string> NN(N), nn(n), rot(n);
    FORI(N)
      cin >> NN[i];
    FORI(n) {
      cin >> nn[i];
      rot[i] = nn[i]; // Initialize rot(ated).
    }
    int ret[4] = {0,0,0,0};
    FORI(4) {
      FORY(N-n+1) {
	FORX(N-n+1) {
	  bool ok = true;
	  for(int xx = 0; xx < n && ok; ++xx) {
	    for(int yy = 0; yy < n && ok; ++yy) {
	      if(NN[y+yy][x+xx] != nn[yy][xx])
		ok = false;
	    }
	  }
	  if(ok)
	    ++ret[i];
	} // FORX
      } // FORY
      // Rotate nn:
      FORY(n) {
	FORX(n) {
	  rot[y][x] = nn[x][n-1-y];
	}
      }
      nn = rot;
    } // FORI
    FORI(4) {
      if(i > 0)
	cout << " ";
      cout << ret[(4-i)%4];
    }
    cout << endl;
  }
}
