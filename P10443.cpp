int main() {
  string a[109], b[109];
  FORCAS {
    if(cas > 0)
      cout << endl;
    GI(r); GI(c); GI(n);
    FORI(r) {
      cin >> a[i];
      b[i] = a[i];
    }
    FORI(n) { // Simulate n generations:
      FORY(r) {
	FORX(c) {
	  char killer;
	  if(a[y][x] == 'P')
	    killer = 'S';
	  else if(a[y][x] == 'R')
	    killer = 'P';
	  else
	    killer = 'R';
	  b[y][x] = ((x > 0   && a[y][x-1] == killer) ||
		     (y > 0   && a[y-1][x] == killer) ||
		     (x < c-1 && a[y][x+1] == killer) ||
		     (y < r-1 && a[y+1][x] == killer)) ? killer : a[y][x];	    
	} // FORX
      } // FORY
      swap(a, b);
    } // FORI
    FORY(r)
      cout << a[y] << endl;
  }
  return 0;
}
