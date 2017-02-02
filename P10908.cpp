int main() {
  FORCAS {
    int w, h, q, x, y; 
    cin >> h >> w >> q; 
    cout << h << " " << w << " " << q << endl;
    char *M = new char[w*h];
    string s;
    FORI(h) {
      cin >> s;
      FORJ(w)
	M[i*w+j] = s[j];
    }
    // Handle queries:
    FORI(q) {
      cin >> y >> x;
      char color = M[y*w+x];
      int radius = 0;
      while(true) {
	++radius;
	// Check bounds:
	if(x-radius < 0 || y-radius < 0 || x+radius == w || y + radius == h)
	  break;

	// Check new square:
	bool ok = true; 
	FORJ(2*radius+1 && ok) {
	  if(M[(y-radius+j)*w+(x-radius)] != color)
	    ok = false;
	  if(M[(y-radius+j)*w+(x+radius)] != color)
	    ok = false;
	  if(M[(y-radius)*w+(x-radius+j)] != color)
	    ok = false;
	  if(M[(y+radius)*w+(x-radius+j)] != color)
	    ok = false;
	}
	if(!ok)
	  break;
      } // white(true)
      cout << 2*(radius-1)+1 << endl;
    }

    delete[] M;
  }
  return 0;
}
