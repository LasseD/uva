int Q[12][12]; // +1, so we don't have to worry about corners

void print() {
  FORY(10) {
    FORX(10) {
      int q = Q[y+1][x+1];
      if(q == -1)
	cout << "*";
      else if(q > 9)
	cout << (char)('a'+q-10);
      else
	cout << q;
    }
    cout << endl;
  }
  cout << endl;
}

int main() {
  LL flashes = 0;
  string s;
  FORY(10) {
    cin >> s;
    FORX(10) {
      Q[y+1][x+1] = s[x]-'0';
    }
  }
  cout << "Input:" << endl;
  print();

  FORI(1000) {
    // First increase:
    FORY(10) {
      FORX(10) {
	Q[y+1][x+1]++;
      }
    }
    
    // Flash:
    bool any = true;
    int f2 = 0;
    while(any) {
      any = false;
      FORY(10) {
	FORX(10) {
	  int q = Q[y+1][x+1];
	  if(q == -1)
	    continue; // Already flashed
	  if(q >= 10) {
	    any = true;
	    f2++;
	    flashes++;
	    Q[y+1][x+1] = -1;
	    for(int yy = y-1; yy <= y+1; yy++) {
	      for(int xx = x-1; xx <= x+1; xx++) {
		if(Q[yy+1][xx+1] != -1)
		  Q[yy+1][xx+1]++;
	      }
	    }
	  }
	} // FORX
      } // FORY      
    } // while any
    //cout << "After step " << (i+1) << ":" << endl;
    //print();
    FORY(10) {
      FORX(10) {
	if(Q[y+1][x+1] == -1)
	  Q[y+1][x+1] = 0;
      }
    }
    if(f2 == 100) {
      cout << "Answer 2: " << (i+1) << endl;
      return 0;
    }
    if(i == 99) {
      cout << "Answer 1: " << flashes << endl;
    }
  } // FORI
}
