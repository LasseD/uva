struct Board {
  int b[5][5];

  int bingo(int X) {
    FORY(5) {
      FORX(5) {
	if(b[y][x] == X) {
	  b[y][x] = -b[y][x]-1;
	}
      }
    }
    // Check:
    bool won = false;
    FORY(5) {
      bool ok = true;
      FORX(5) {
	if(b[y][x] >= 0) {
	  ok = false;
	  break;
	}
      }
      if(ok)
	won = true;
    }
    FORX(5) {
      bool ok = true;
      FORY(5) {
	if(b[y][x] >= 0) {
	  ok = false;
	  break;
	}
      }
      if(ok)
	won = true;
    }
    if(!won)
      return -1;
    int ret = 0;
    FORY(5) {
      FORX(5) {
	if(b[y][x] >= 0) {
	  ret += b[y][x];
	}
      }
    }
    return ret * X;
  }
};

int main() {
  vector<int> v;
  int x; string s;
  {
    getline(cin, s);
    stringstream ss; ss << s;
    while(ss >> x) {
      v.push_back(x);
    }
  }
  // Read boards:
  Board boards[1000];
  int size = 0;
  while(getline(cin, s)) {
    Board &b = boards[size++];
    FORY(5) {
      getline(cin, s);
      stringstream ss; ss << s;
      FORX(5) {
	ss >> b.b[y][x];
      }
    }
  }
  // Simulate:
  bool *won = new bool[size];
  FORI(size)
    won[i] = false;
  FORUI(v.size()) {
    int x = v[i];
    FORJ(size) {
      if(won[j])
	continue; // Already won.
      int v = boards[j].bingo(x);
      if(v >= 0) {
	cout << "Board " << j << " wins with: " << v << endl;
	won[j] = true;
      }      
    }
  }
}
