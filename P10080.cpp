// Use Ford-Fulkerson for maximum bipartite matching (maximum cardinality bipartite matching). See http://www.geeksforgeeks.org/maximum-bipartite-matching/
int n, m, assignedGopher[100];
bool seen[100];
vector<int> okHoles[100];

bool bpm(int gopher) { // DFS-based function trying all holes for gopher.
  // First find a free hole:
  FORIT(vector<int>, okHoles[gopher]) {
    int i = *it;
    if(seen[i])
      continue;
    seen[i] = true;
    if(assignedGopher[i] == -1 || bpm(assignedGopher[i])) {
      assignedGopher[i] = gopher;
      return true;
    }
  }
  return false;
}

int maxFlow() {
  int ret = 0;
  FORI(n) { // Try to improve life for all gophers:
    memset(seen, false, sizeof(seen));
    if(bpm(i))
      ++ret;
  }
  return ret;
}

double distSq(PD a, PD b) {
  double dx = a.XX-b.XX;
  double dy = a.YY-b.YY;
  return dx*dx+dy*dy;
}

int main() {
  long s, v; // n gophers, m holes, s seconds, v gopher speed.
  PD gophers[100], holes[100];

  while(cin >> n >> m >> s >> v) {
    FORI(n)
      cin >> gophers[i].XX >> gophers[i].YY;
    FORI(m)
      cin >> holes[i].XX >> holes[i].YY;

    memset(assignedGopher, -1, sizeof(assignedGopher));
    // Compute edges:
    FORI(n) {
      okHoles[i].clear();
      FORJ(m) {
	if(distSq(gophers[i], holes[j]) <= s*v*s*v)
	  okHoles[i].push_back(j);
      }
    }

    cout << n-maxFlow() << endl;
  }
  return 0;
}
