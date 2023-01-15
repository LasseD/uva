// Cleanup input: RM "with position ", "with letter ", "to position ", "on position of letter "
// Add starting string to top of input.
// For part 2 use "reverse-region" to reverse lines of input file in emacs.
int main() {
  GS(s);
  int reverseRotations[10];
  FORI((int)s.size()) {
    reverseRotations[i] = -1;
  }
  FORI((int)s.size()) { // i is where letter is found.
    int moves = i;
    if(i >= 4) {
      moves++;
    }
    moves++;
    moves = moves % s.size();

    int endPosition = (i+moves)%s.size();
    // i is start position
    // move is i -> endPosition, so reverse move is:
    reverseRotations[endPosition] = (-(endPosition-i)+s.size())%s.size();
  }

  string op, op2;
  char c, d;
  int a, b, ops=0;  
  while(cin >> op) {
    cout << "Operation " << ops++ << ": " << op << endl;
    if(op == "swap") {
      cin >> op2;
      if(op2 == "position") {
	cin >> a >> b;
	swap(s[a],s[b]);
      }
      else if(op2 == "letter") {
	cin >> c >> d;
	FORUI(s.size()) {
	  if(s[i] == c)
	    s[i] = d;
	  else if(s[i] == d)
	    s[i] = c;
	}
      }
    }
    else if(op == "move") {
      //cin >> op2 >> a >> b; // Part 1
      cin >> op2 >> b >> a; // Part 2
      c = s[a];
      // Remove c:
      for(int i = a; i+1 < (int)s.size(); i++) {
	s[i] = s[i+1];
      }
      // Insert c:
      for(int i = (int)s.size()-1; i-1 >= b; i--) {
	s[i] = s[i-1];
      }
      s[b] = c;
    }
    else if(op == "rotate") {
      cin >> op2;
      if(op2 == "right") {
	cin >> a >> op2;
	a = s.size()-a; // Part 2 only
      }
      else if(op2 == "left") {
	cin >> a >> op2;
	//a = s.size()-a; // Part 1 only
      }
      else if(op2 == "based") {
	cin >> c;
	a = -1;
	FORUI(s.size()) {
	  if(s[i] == c) {
	    if(a != -1) {
	      cerr << "Multiple instances of " << c << endl;
	      die();
	    }
	    a = (int)i;
	  }
	}

	a = reverseRotations[a]; // Part 2
	
	/* Part 1:
	if(a>=4)
	  a++;
	a++;
	a = a%s.size();//*/
      }

      FORI(a) {
	c = s[s.size()-1];
	for(int j = (int)s.size()-1; j > 0; j--) {
	  s[j] = s[j-1];
	}
	s[0] = c;
      }
      
    }
    else if(op == "reverse") {
      cin >> op2 >> a >> op2 >> b;
      while(a < b) {
	swap(s[a],s[b]);
	a++;
	b--;
      }
    }
    else {
      cerr << "Unknown operation " << op << endl;
      die();
    }
    cout << "-> " << s << endl;
  }

  cout << s << endl;
}
