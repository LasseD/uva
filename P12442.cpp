#define LIM 50001
bool visited[LIM], marked[LIM];
int nxt[LIM], ret[LIM];

int main() {
  int x, y;
  FORCAS {
    GI(N);
    FORI(N) {
      cin >> x >> y; --x; --y;
      nxt[x] = y;
      visited[x] = marked[x] = false;
    }
    int best = 0;
    // GO:
    FORI(N) {
      if(visited[i])
	continue; // already visited.
      x = i;
      int steps = 0;
      while(!visited[x] && !marked[x]) {
	ret[x] = steps++;
	marked[x] = true;
	x = nxt[x];
      }
      if(!visited[x]) { // marked[x] == true
	// New loop found:
	int loopSize = steps - ret[x];
	steps = ret[x];
	//cerr << "Loop of size " << loopSize << " found." << endl;
	// Mark all in loop:
	ret[x] = loopSize;
	marked[x] = false;
	visited[x] = true;
	y = nxt[x];
	while(y != x) {
	  ret[y] = loopSize;
	  marked[y] = false;
	  visited[y] = true;
	  y = nxt[y];
	}
      }
      // Feed into already visited:
      y = i;
      while(y != x) {
	ret[y] = steps + ret[x];
	marked[y] = false;
	visited[y] = true;
	y = nxt[y];
	--steps;
      }
      if(ret[i] > ret[best])
	best = i;
    }
    /*
    FORI(N)
      cerr << " ret[" << i << "]=" << ret[i] << endl;*/
    cout << "Case " << cas+1 << ": " << best+1 << endl;
  }
  return 0;
}
