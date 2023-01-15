// RM "must be finished before step ", "Step " and " can begin." from input
// Add time penalty and number of workers to beginning of input
int main() {
  GI(penalty); GI(workers);
  char c1, c2;
  int blockers[26], blockers2[26];
  vector<char> blocking[26];
  set<char> seen;
  FORI(26)
    blockers[i] = blockers2[i] = 0;
  while(cin >> c1 >> c2) {
    // c1 blocks c2;
    blocking[c1-'A'].push_back(c2);
    blockers[c2-'A']++;
    blockers2[c2-'A']++;
    seen.insert(c1);
    seen.insert(c2);
  }
  set<char> ready, ready2;
  FORI(26) {
    if(seen.find((char)('A'+i)) != seen.end() && blockers[i] == 0) {
      ready.insert((char)('A'+i));
      ready2.insert((char)('A'+i));
    }
  }
  vector<char> order;
  // Part 1:
  while(!ready.empty()) {
    char c = *ready.begin();
    ready.erase(ready.begin());
    cout << c;
    order.push_back(c);
    FORIT(vector<char>, blocking[c-'A']) {
      char c2 = *it;
      blockers[c2-'A']--;
      if(blockers[c2-'A'] == 0) {
	ready.insert(c2);
      }
    }
  }
  cout << endl;
  // Part 2: Simulate construction with 5 workers:
  int time = 0;
  int remainingItems = (int)seen.size();
  int remaining[26];
  FORI(26) {
    remaining[i] = penalty + 1 + i;
  }
  for(; remainingItems > 0; time++) {
    if(ready2.empty()) {
      cerr << "Nothing to work on!" << endl;
      return 2;
    }
    // Find items that can be worked on:
    vector<char> toRemove, toInsert;
    // Take those that are finished soonest:
    vector<PIC> v3;
    FORIT(set<char>, ready2) {
      char c = *it;
      v3.push_back(PI(-remaining[c-'A'], c));
    }
    sort(v3.begin(), v3.end());
    
    int workers2 = 1;
    cout << "Time " << time << " working on";
    FORIT(vector<PIC>, v3) {
      if(workers2++ > workers) {
	break; // Not enough workers.
      }
      char c = it->second;
      remaining[c-'A']--;
      cout << " " << c << " (" << remaining[c-'A'] << ")";
      if(remaining[c-'A'] == 0) {
	//cout << "After " << time << ", item " << c << " is done. Reduce blocking for: " << blocking[c-'A'].size() << endl;
	toRemove.push_back(c);
	FORIT2(vector<char>, blocking[c-'A']) {
	  char c2 = *it2;
	  blockers2[c2-'A']--;
	  if(blockers2[c2-'A'] == 0) {
	    //cout << "Now ready: " << c2 << endl;
	    toInsert.push_back(c2);
	  }
	}
	remainingItems--;
      }
    }
    cout << endl;
    FORIT(vector<char>, toRemove) {
      ready2.erase(*it);
    }
    FORIT(vector<char>, toInsert) {
      ready2.insert(*it);
    }
  } // for ;
  cout << "Answer 2: " << time << endl; // [1102 1108]
}
