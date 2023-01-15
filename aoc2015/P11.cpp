void next(string &pw, int idx) {
  if(pw[idx] == 'z') {
    pw[idx] = 'a';
    next(pw, idx-1);
  }
  else {
    pw[idx]++;
  }  
}
void next(string &pw) {
  next(pw, 7);
}

bool check(string &pw) {
  bool ok = false;
  int len = (int)pw.size();
  for(int i = 0; i+2 < len; i++) {
    if(pw[i]+2 == pw[i+1]+1 && pw[i+1]+1 == pw[i+2]+0) {
      ok = true;
      break;
    }
  }
  if(!ok) {
    cout << "  " << pw << " has not incrementing 3" << endl;
    return false;
  }
  FORI(len) {
    char c = pw[i];
    if(c == 'o' || c == 'i' || c == 'l') {
      cout << "  " << pw << " contains illegal letter" << endl;
      pw[i]++; // Quick skip.
      return false;
    }
  }
  ok = false;
  FORI(len-3) {
    if(pw[i] == pw[i+1]) {
      for(int j = i+2; j+1 < len; j++) {
	if(pw[j] == pw[j+1]) {
	  ok = true;
	  break;
	}
      }
    }
    if(ok) {
      break;
    }
  }
  if(!ok) {
    cout << "  " << pw << " Missing double pairs" << endl;
  }
  return ok;
}

int main() {
  GS(pw);
  do {
    next(pw);
  } while(!check(pw));
  cout << pw << endl;
}
