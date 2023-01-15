// Remove "," and ":" from input and add Sue 501 as stopper at end.
typedef map<string,int> MAP;

int main() {
  GI(N);
  MAP goal;
  set<string> zero;
  FORI(N) {
    GS(key);
    GI(val);
    if(val == 0) {
      zero.insert(key);
    }
    goal[key] = val;
  }
  GS(ignore);
  GI(one);

  string key;
  int val;
  MAP cur;
  
  while(cin >> key >> val) {
    if(key == "Sue") {
      int sue = val-1;
      // Check Sue:
      bool ok = true;
      FORIT(MAP, cur) {
	key = it->first;
	val = it->second;
	if(key == "cats" || key == "trees") {
	  if(goal[key] >= val) {
	    ok = false;
	    break;
	  }
	  // More
	}
	else if(key == "pomeranians" || key == "goldfish") {
	  if(goal[key] <= val) {
	    ok = false;
	    break;
	  }
	}
	else {
	  if(goal[key] != val) {
	    ok = false;
	    break;
	  }
	}
      }
      if(ok) {
	cout << "MATCH! " << sue << endl;
      }
      cur.clear();
    }
    else {
      cur[key] = val;
    }
  }
}
