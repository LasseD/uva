void add(string &s, set<char> &S) {
  FORUI(s.size()) {
    char c = s[i];
    if(S.find(c) == S.end())
      S.insert(c);
  }
}

void intersect(string &s, set<char> &S) {
  set<char> ss;
  FORUI(s.size()) {
    char c = s[i];
    if(S.find(c) != S.end())
      ss.insert(c);
  }
  S = ss;
}

int main() {
  FORCAS {
    set<char> heavy, light, even;
    bool firstUneven = true;
    FORI(3) {
      GS(left); GS(right); GS(type);
      if(type[0] == 'e') {
	add(left, even);
	add(right, even);
      }
      else if(type[0] == 'u') {
	if(firstUneven) {
	  add(left, heavy);
	  add(right, light);
	  firstUneven = false;
	}
	else {
	  intersect(left, heavy);
	  intersect(right, light);
	}
      }
      else {
	if(firstUneven) {
	  add(right, heavy);
	  add(left, light);
	  firstUneven = false;
	}
	else {
	  intersect(right, heavy);
	  intersect(left, light);
	}
      }
    }
    for(char c = 'A'; c <= 'L'; ++c) {
      bool e = even.find(c) != even.end();
      bool h = heavy.find(c) != heavy.end();
      bool l = light.find(c) != light.end();
      if(e || (h && l) || (!e && !h && !l))
	continue; // Not counterfit.
      cout << c << " is the counterfeit coin and it is ";
      if(h)
	cout << "heavy." << endl;
      else
	cout << "light." << endl;
    }
  }
  return 0;
}
