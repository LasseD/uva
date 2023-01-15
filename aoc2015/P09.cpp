typedef pair<int,PS> PISS;
#define BIG 9999999

map<string,int> clusters;
set<string> ids;
int D[10][10];
bool used[10];

int bestDist(int from, int left) {
  if(left == 0)
    return 0;
  int best = 0; // BIG for part 1
  FORI((int)ids.size()) {
    if(used[i])
      continue;
    if(D[from][i] == BIG) {
      continue;
    }
    used[i] = true;
    best = max(best, D[from][i] + bestDist(i, left-1));
    used[i] = false;
  }
  return best;
}

int main() {
  int dist, answer = 0; // BIG for part 1;
  FORI(10) {
    FORJ(10) {
      D[i][j] = BIG;
    }
  }
  string a, s, b;
  while(cin >> a >> s >> b >> s >> dist) {
    if(ids.find(a) == ids.end()) {
      clusters[a] = (int)clusters.size();
      ids.insert(a);
    }
    if(ids.find(b) == ids.end()) {
      clusters[b] = (int)clusters.size();
      ids.insert(b);
    }
    D[clusters[b]][clusters[a]] = D[clusters[a]][clusters[b]] = dist;
  }

  // Try to start for each:
  FORJ((int)ids.size()) {
    FORI(10) {
      used[i] = false;
    }
    used[j] = true;
    answer = max(answer, bestDist(j, (int)ids.size()-1));
  }
  
  cout << "Answer: " << answer << endl;
}
