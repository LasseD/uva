typedef map<ULL,int> MAP;

ULL encode(int *board) {
  ULL ret = 0;
  FORI(9) {
    ret = 10*ret+board[i];
  }
  return ret;
}

void decode(ULL encoded, int *board) {
  FORI(9) {
    board[8-i] = encoded % 10;
    encoded /= 10;
  }
}

void rotX(int x, int *board) {
  swap(board[x+6], board[x+3]);
  swap(board[x], board[x+3]);
}
void revX(int x, int *board) {
  swap(board[x], board[x+3]);
  swap(board[x+6], board[x+3]);
}
void rotY(int y, int *board) {
  swap(board[3*y], board[3*y+1]);
  swap(board[3*y+2], board[3*y+1]);
}
void revY(int y, int *board) {
  swap(board[3*y+2], board[3*y+1]);
  swap(board[3*y], board[3*y+1]);
}

void addAll(int *board, vector<ULL> &v2, MAP &m) {
  for(int x = 2; x >= 0; --x) {
    rotX(x, board);
    ULL enc = encode(board);
    if(m.find(enc) == m.end()) {
      m.insert(make_pair(enc, x+1));
      v2.push_back(enc);
    }
    revX(x, board);
  }
  for(int y = 2; y >= 0; --y) {
    rotY(y, board);
    ULL enc = encode(board);
    if(m.find(enc) == m.end()) {
      m.insert(make_pair(enc, -(y+1)));
      v2.push_back(enc);
    }
    revY(y, board);
  }
}

ULL buildMap(MAP &m) {
  int board[9] = {1,2,3,4,5,6,7,8,9};

  vector<ULL> v;
  ULL enc = encode(board);
  v.push_back(enc);
  m.insert(make_pair(enc, 0));
  
  while(!v.empty()) {
    vector<ULL> v2;
    FORIT(vector<ULL>, v) {
      ULL candidate = *it;
      decode(candidate, board);
      addAll(board, v2, m);
    }
    v = v2;
  }
  return enc; // Base.
}

int main() {
  MAP m;
  ULL baseEnc = buildMap(m);
  /*
  cerr << "|M|=" << m.size() << ", baseEnc=" << baseEnc << endl;
  // First 10:
  int ignore = 0;
  FORIT(MAP, m) {
    if(10 == ignore++)
      break;
    cout << it->first << ": " << it->second << endl;
  }//*/

  int board[9];

  while(true) {
    cin >> board[0];
    if(board[0] == 0)
      return 0;
    FORI(8)
      cin >> board[i+1];
    ULL enc = encode(board);
    //cerr << "enc=" << enc << endl;
    // Find result:
    if(m.find(enc) != m.end()) {
      vector<int> s;
      while(enc != baseEnc) {
	int move = m[enc];
	s.push_back(move);
	if(move > 0)
	  revX(move-1, board);
	else
	  revY(-move-1, board);
	enc = encode(board);
      }
      cout << s.size() << " ";
      FORIT(vector<int>, s) {
	if(*it > 0)
	  cout << "V" << *it;
	else
	  cout << "H" << -(*it);
      }
      cout << endl;
    }
    else {
      cout << "Not solvable" << endl;
    }
  }
}
