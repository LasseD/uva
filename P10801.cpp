typedef pair<int,PI> WeightAndSource; // Source being level, elevator.

#define INF 999999
#define OLD_INF numeric_limits<int>::max()
#define LEVEL first
#define ELEVATOR second

/*
Dijkstra for shortest path. 
N vertices
M edges
 */
void dijkstra(int N, int k, int *T, bool visits[][100] ) {
  if(k == 0) {
    cout << 0 << endl;
    return;
  }

  bool visited[100]; // Visited floors.
  int minPath[100]; // Min time for floors.
  for(int i = 0; i < 100; ++i) {
    visited[i] = false;
    minPath[i] = INF;
  }
  minPath[0] = 0;

  set<WeightAndSource> Q; // To visit
  FORI(N) {
    if(!visits[i][0])
      continue; // Can't take this first :(
    for(int j = 1; j < 100; ++j) {
      if(visits[i][j])
	Q.insert(WeightAndSource(j*T[i], PI(j,i))); // Travel time, destination.
    }
  }

  while(!Q.empty()) {
    const WeightAndSource p = *Q.begin();
    Q.erase(Q.begin());
    const int weight = p.first;
    const PI from = p.second;
    if(visited[from.LEVEL])
      continue; // Level already visited
    //cerr << "Taking elevator " << from.ELEVATOR << " to level " << from.LEVEL << " at time " << weight << endl;
    if(from.LEVEL == k) {
      break; // done!
    }

    // perform relaxation:
    visited[from.LEVEL] = true;
    FORI(N) { // elevator
      if(!visits[i][from.LEVEL])
	continue; // Can't take this!
      if(i == from.ELEVATOR)
	continue; // We came from this.
      for(int j = 1; j < 100; ++j) {
	if(!visits[i][j] || visited[j])
	  continue;
	int diff = j-from.LEVEL;
	if(diff < 0)
	  diff = -diff;
	int newCost = weight + 60 + diff*T[i];
	if(newCost > minPath[j])
	  continue;
	minPath[j] = newCost;
	Q.insert(WeightAndSource(newCost, PI(j,i))); // Travel time, destination.
      } // for j
    } // FORI
  } // WHILE Q not empty

  if(minPath[k] == INF)
    cout << "IMPOSSIBLE" << endl;
  else
    cout << minPath[k] << endl;
}

int main() {
  int N, k, x, T[5]; // Times for elevator 1..5 to travel between floors.
  string line;
  bool visits[5][100];

  while(true) {
    if(!(cin >> N >> k))
      return 0;
    FORI(N) {
      cin >> T[i];
      FORJ(100)
	visits[i][j] = false;
    }
    cin.ignore(); // Skip newline.
    FORI(N) {
      //cerr << "Elevator " << i << " visits";
      getline(cin, line);
      stringstream ss; ss << line;
      while(ss >> x) {
	visits[i][x] = true;
	//cerr << " " << x;
      }
      //cerr << endl;
    }

    dijkstra(N, k, T, visits);
  }
}
