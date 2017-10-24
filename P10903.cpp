int main() {
  int wins[101], total[101];
  bool first = true;
  while(true) {
    GI(n); if(n == 0) return 0;
    GI(k);
    if(!first)
      printf("\n");
    first = false;
    memset(wins, 0, sizeof(wins));
    memset(total, 0, sizeof(total));
    long all = k*n*(n-1)/2;
    FORI(all) {
      GI(a); GS(sa); GI(b); GS(sb); --a; --b;
      char ca = sa[0], cb = sb[0];
      if(ca != cb) {
	total[a]++;
	total[b]++;
	if(ca == 'r') {
	  if(cb == 's')
	    wins[a]++;
	  else
	    wins[b]++;
	}
	else if(ca == 'p') {
	  if(cb == 'r')
	    wins[a]++;
	  else
	    wins[b]++;	    
	}
	else { // ca == 's'
	  if(cb == 'p')
	    wins[a]++;
	  else
	    wins[b]++;	    
	}
      }
    } // FORI
    FORI(n) {
      if(total[i] == 0)
	printf("-\n");
      else
	printf("%.3f\n", wins[i]/(double)total[i]);
    }
  } // while(true)
} // int main
