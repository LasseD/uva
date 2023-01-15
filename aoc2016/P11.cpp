// Clean up input, so it matches the example from the problem statement:
// Line: <number of items> <item>* with <item> = X[MG], X=0,1,...
#define SIZE 7

unsigned int G[SIZE], M[SIZE], elevator = 0, size; // Floors and elevator

void print() {
  FORI(4) {
    unsigned int f = 4-i-1;
    cout << "F" << (f+1) << " ";
    if(elevator == f)
      cout << "E ";
    else
      cout << ". ";
    FORJ(size) {
      if(G[j] == f)
	cout << j << "G ";
      else
	cout << ".  ";
      if(M[j] == f)
	cout << j << "M ";
      else
	cout << ".  ";
    }
    cout << endl;
  }
}

void decode(ULL x) {
  FORI(size) {
    M[size-1-i] = x & 3;
    x >>= 2;
  }
  FORI(size) {
    G[size-1-i] = x & 3;
    x >>= 2;
  }
  elevator = x;
  // Check if state is valid:
  bool ok = false;
  FORI(size) {
    if(elevator == M[i] || elevator == G[i]) {
      ok = true;
      break;
    }
  }
  if(!ok) {
    print();
    cerr << "Invalid state!" << endl;
    die();
  }
}

ULL encode() {
  ULL ret = elevator;
  FORI(size) {
    ret = (ret << 2) + G[i];
  }
  FORI(size) {
    ret = (ret << 2) + M[i];
  }
  return ret;
}

bool isValid() {
  FORI(size) {
    unsigned int m = M[i];
    unsigned int g = G[i];
    if(m != g) {
      FORJ(size) {
	if(G[j] == m)
	  return false; // Generator at unshielded m
      }
    }
  }
  return true;
}

bool isDone() {
  if(elevator != 3)
    return false;
  FORI(size) {
    if(M[i] != 3)
      return false;
    if(G[i] != 3)
      return false;
  }
  return true;
}

int main() {
  // Read input file (modified):
  cin >> size;
  FORJ(3) {
    GI(Q);
    FORI(Q) {
      GS(s);
      unsigned int id = s[0]-'0';
      if(s[1] == 'G') {
	G[id] = j;
	cout << "Generator " << id << " on floor " << j << endl;
      }
      else {
	M[id] = j;
	cout << "Microchip " << id << " on floor " << j << endl;
      }
    }
  }

  // Simulate all possibilities:
  set<ULL> s1, s2, seen;
  ULL state = encode();
  s1.insert(state);
  seen.insert(state);
  cout << "Initial encoded state: " << state << endl;

  for(unsigned int iteration = 0; !s1.empty(); iteration++) {
    cout << "Handling iteration " << iteration << ", states: " << s1.size() << endl;
    FORIT(set<ULL>, s1) {
      state = *it;
      decode(state);

      //cout << "Iteration " << iteration << " state:" << endl;
      //print();
      
      if(isDone()) {
	cout << "Answer: " << iteration << endl;
	return 0;
      }

      // Try all movements and place in s2:
      vector<PCI> stuff;
      FORI(size) {
	if(M[i] == elevator) {
	  stuff.push_back(PCI('M',i));
	}
	if(G[i] == elevator) {
	  stuff.push_back(PCI('G',i));
	}
      }
      // Try to move one thing:
      ULL oldState = encode();
      FORUI(stuff.size()) {
	bool isM = stuff[i].first == 'M';
	int id = stuff[i].second;
	if(elevator > 0) { // Elevator down:
	  elevator--;
	  if(isM) {
	    M[id]--;
	  }
	  else {
	    G[id]--;
	  }
	  if(isValid()) {
	    ULL x = encode();
	    if(seen.find(x) == seen.end()) {
	      seen.insert(x);
	      s2.insert(x);
	    }
	  }
	  decode(oldState);
	}
	if(elevator < 3) { // Elevator Up:
	  elevator++;
	  if(isM) {
	    M[id]++;
	  }
	  else {
	    G[id]++;
	  }
	  if(isValid()) {
	    ULL x = encode();
	    if(seen.find(x) == seen.end()) {
	      seen.insert(x);
	      s2.insert(x);
	    }
	  }
	  decode(oldState);
	}
      }
      // Try to move two things:
      FORI((int)stuff.size()-1) {
	for(int j = i+1; j < (int)stuff.size(); j++) {
	  bool isMI = stuff[i].first == 'M';
	  int idI = stuff[i].second;
	  bool isMJ = stuff[j].first == 'M';
	  int idJ = stuff[j].second;
	  if(elevator > 0) { // Elevator down:
	    elevator--;
	    if(isMI) {
	      M[idI]--;
	    }
	    else {
	      G[idI]--;
	    }
	    if(isMJ) {
	      M[idJ]--;
	    }
	    else {
	      G[idJ]--;
	    }
	    if(isValid()) {
	      ULL x = encode();
	      if(seen.find(x) == seen.end()) {
		seen.insert(x);
		s2.insert(x);
	      }
	    }
	    decode(oldState);
	  }
	  if(elevator < 3) { // Elevator Up:
	    elevator++;
	    if(isMI) {
	      M[idI]++;
	    }
	    else {
	      G[idI]++;
	    }
	    if(isMJ) {
	      M[idJ]++;
	    }
	    else {
	      G[idJ]++;
	    }
	    if(isValid()) {
	      ULL x = encode();
	      if(seen.find(x) == seen.end()) {
		seen.insert(x);
		s2.insert(x);
	      }
	    }
	    decode(oldState);
	  } // if elevator
	} // for j
      } // FORI
    } // FORIT(s1)
    
    swap(s1, s2);
    s2.clear();
  }
  cout << "Impossible!" << endl;
}
