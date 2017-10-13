bool visited[101];
string names[101];
vector<int> g[101];
int n;

void visitSubGraph(int x) {
  visited[x] = true;
  FORIT(vector<int>, g[x]) {
    if(!visited[*it])
      visitSubGraph(*it);
  }
}

bool isCritical(int x) {
  FORI(n)
    visited[i] = false;
  visited[x] = true;

  int unvisitedSubGraphs = 0;
  FORIT(vector<int>, g[x]) {
    if(visited[*it])
      continue;
    visitSubGraph(*it);
    unvisitedSubGraphs++;
  }
  return unvisitedSubGraphs > 1;
}

int main() {
  int m, x, y;
  string s1, s2;
  
  for(int cas = 1; true; ++cas) {
    // Read input:
    cin >> n;
    if(n == 0)
      return 0;
    FORI(n) {
      cin >> names[i];
    }
    sort(names, names+n);
    map<string,int> M;
    FORI(n) {
      M[names[i]] = i;
      g[i].clear();
    }
    cin >> m;
    FORI(m) {
      cin >> s1 >> s2;
      x = M[s1];
      y = M[s2];
      g[x].push_back(y);
      g[y].push_back(x);
    }
    
    // Compute output:
    if(cas != 1)
      cout << endl;
    vector<int> ret;

    FORI(n) {
      if(isCritical(i))
	ret.push_back(i);
    }
    
    cout << "City map #" << cas << ": " << ret.size() << " camera(s) found" << endl;
    FORIT(vector<int>, ret)
      cout << names[*it] << endl;
  }
}
