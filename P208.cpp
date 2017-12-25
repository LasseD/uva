bool visited[20], reachVisit[20];
vector<int> G[20];
int FIRE, S[20], sizeS;

bool reachable(int from) {
  if(from == FIRE)
    return true;
  reachVisit[from] = true;
  FORIT(vector<int>, G[from]) {
    int n = *it;
    if(visited[n] || reachVisit[n])
      continue;
    if(reachable(n))
      return true;
  }
  return false;
}

int go(int from) {
  if(from == FIRE) {
    printf("%d", S[0]+1);
    for(int i = 1; i < sizeS; ++i)
      printf(" %d", S[i]+1);
    printf(" %d\n", FIRE+1);
    return 1;
  }

  // Check reachable:
  memset(reachVisit, false, sizeof(reachVisit));
  if(!reachable(from))
    return 0;//*/

  visited[from] = true;
  S[sizeS++] = from;
  int ret = 0;
  FORIT(vector<int>, G[from]) {
    int n = *it;
    if(!visited[n])
      ret += go(n);
  }
  visited[from] = false;
  --sizeS;
  return ret;
}

int main() {
  for(int cas = 1; cin >> FIRE; ++cas) {
    // Reset:
    --FIRE;
    FORI(20) {
      G[i].clear();
      visited[i] = false;
    }
    sizeS = 0;

    //Read data:
    while(true) {
      GI(a); GI(b); if(a == 0 && b == 0) break;
      G[a-1].push_back(b-1);
      G[b-1].push_back(a-1);
    }
    FORI(20)
      sort(G[i].begin(), G[i].end()); // Ensure DFS goes

    // GO!
    printf("CASE %d:\n", cas);
    int ret = go(0);
    printf("There are %d routes from the firestation to streetcorner %d.\n", ret, FIRE+1);
  }
  return 0;
}
