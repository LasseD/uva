// Remove comma from input
set<int> neighbours[2000];

int main() {
  string s;

  int size = 0, a, b;
  while(getline(cin, s)) {
    stringstream ss; ss << s;
    ss >> a >> s;
    while(ss >> b) {
      neighbours[a].insert(b);
      neighbours[b].insert(a);
    }
    size++;
  }
  // Comput group with 0:
  set<int> seen;
  int groups = 0;
  for(int x = 0; x < size; x++) {
    if(seen.find(x) != seen.end())
      continue; // Already handled
    
    stack<int> ready;
    ready.push(x);
    while(!ready.empty()) {
      int x = ready.top(); ready.pop();
      if(seen.find(x) != seen.end())
	continue; // Already handled
      seen.insert(x);
      FORIT(set<int>, neighbours[x]) {
	int y = *it;
	if(seen.find(y) == seen.end()) {
	  ready.push(y);
	}
      }
    }
    if(groups == 0)
      cout << "Answer 1: " << seen.size() << endl;

    groups++;
  }
  cout << "Answer 2: " << groups << endl;
}
