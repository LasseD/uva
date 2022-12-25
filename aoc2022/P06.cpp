// For problem A, use '4' instead of '14'
int main() {
  bool seen[26];
  GS(s);
  for(int i = 14; true; i++) {
    FORJ(26){
      seen[j] = false;
    }
    bool ok = true;
    FORJ(14) {
      int pos = s[i-14+j]-'a';
      if(seen[pos]) {
	ok = false;
	break;
      }
      seen[pos] = true;
    }
    if(ok) {
      cout << "Answer 1: " << i << endl;
      break;
    }
  }
  
} // int main
