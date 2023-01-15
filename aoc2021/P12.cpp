bool used[100];
int idStart, idEnd;
map<string,int> ids;
set<string> con[100];

LL numPaths(int from, bool twiceVisited) {
  if(from == idEnd) {
    return 1;
  }
  LL ret = 0;
  FORIT(set<string>, con[from]) {
    string s = *it;
    int id = ids[s];
    if(id == idStart)
      continue;

    // See if we can visit:
    bool twiceNow = twiceVisited;
    if(used[id]) {
      if(twiceNow)
	continue; // Already in use
      twiceNow = true;
    }

    bool switched = false;
    if(!used[id] && s[0] >= 'a' && s[0] <= 'z') {
      used[id] = true;
      switched = true;
    }
    
    ret += numPaths(id, twiceNow);
    
    if(switched)
      used[id] = false;
  }
  return ret;
}

// Replace - with space in input
int main() {
  FORI(100) used[i] = false;
  string a, b;
  while(cin >> a >> b) {
    if(ids.find(a) == ids.end())
      ids[a] = (int)ids.size();
    if(ids.find(b) == ids.end())
      ids[b] = (int)ids.size();
    con[ids[a]].insert(b);
    con[ids[b]].insert(a);
  }
  cout << "Read " << ids.size() << " caves" << endl;

  idStart = ids["start"];
  idEnd = ids["end"];
  used[idStart] = true;
  
  LL answer1 = numPaths(idStart, false);
  cout << answer1 << endl;
}
