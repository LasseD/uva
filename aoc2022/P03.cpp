int prio(char c) {
  if(c >= 'a' && c <= 'z')
    return c-'a'+1;
  return c-'A'+27;
}

int main() {
  int sum = 0, sum2 = 0, line = 0;
  bool seen[52], seen2[52];
  string s, prev, prevprev;
  while(cin >> s) {
    line++;
    FORI(52) seen[i] = false; // Reset

    // Check compartment 1:
    int half = ((int)s.size())/2;
    FORI(half) seen[prio(s[i])-1] = true;

    FORI(half) {
      int p = prio(s[i+half]);
      if(seen[p-1]) {
	sum += p;
	break;
      }
    }

    if(line%3 == 0) {
      FORI(52) seen[i] = false; // Reset
      FORI(52) seen2[i] = false; // Reset
      FORUI(prevprev.size()) seen[prio(prevprev[i])-1] = true;
      FORUI(prev.size()) seen2[prio(prev[i])-1] = true;
      FORUI(s.size()) {
	int p = prio(s[i]);
	if(seen[p-1] && seen2[p-1]) {
	  sum2 += p;
	  break;
	}
      }
      
    }
    
    prevprev = prev;
    prev = s;
  }
  cout << "Answer 1: " << sum << endl;
  cout << "Answer 2: " << sum2 << endl;
} // int main
