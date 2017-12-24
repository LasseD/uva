int main() {
  string s;
  vector<char> v[7];
  while(true) {
    if(!getline(cin, s))
      return 0;
    FORI(7)
      v[i].clear();
    int bits = 1;
    int size = 2;
    int idx = 0;
    FORUI(s.size()) {
      //cerr << bits << " -> " << s[i] << endl;
      v[bits-1].push_back(s[i]);
      ++idx;
      if(idx == size-1) {
	size*=2;
	++bits;
	idx = 0;
      }	
    }

    bool part1 = true;
    idx = 0;
    int val = 0;
    int length = 0;
    bool done = false;
    while(!done) {
      if(!getline(cin, s))
	die();
      FORUI(s.size()) {
	int bit = s[i]-'0';
	if(part1) {
	  length = (length << 1 ) + bit;
	  ++idx;
	  if(idx == 3) {
	    //cerr << "L=" << length;
	    if(length == 0) {
	      done = true;
	      break; // Decoding done.
	    }
	    idx = 0;
	    val = 0;
	    part1 = false;
	  }
	}
	else {
	  val = (val << 1 ) + bit;
	  ++idx;
	  if(idx == length) {
	    //cerr << ",V=" << val;
	    if(val >= (int)v[length-1].size()) {
	      // All 1's => 
	      length = 0;
	      part1 = true;
	    }
	    else {
	      cout << v[length-1][val];
	      val = 0;
	    }
	    idx = 0;
	  }	  
	}
      } // FORUI
    } // while(!done)
    cout << endl;
  } // while(true) MAIN LOOP
} // int main
