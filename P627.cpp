#define INF 999999

void walk(int a, int b, int PREV[][301]) {
  if(PREV[a][b] != a) {
    walk(a, PREV[a][b], PREV);
    walk(PREV[a][b], b, PREV);
  }
  else
    cout << " " << b+1;
}

int main() {
  int COST[301][301];
  int PREV[301][301];

  int M; // M routers
  while(cin >> M) {
    cout << "-----" << endl;

    // Set adjacency matrix:
    FORI(M) {
      FORJ(M) {
	COST[i][j] = INF;
      }
    }
    FORI(M) {
      COST[i][i] = 0;
      PREV[i][i] = i;
    }
    FORI(M) {
      string s; cin >> s;
      FORUJ(s.size()) {
	if(s[j] == '-' || s[j] == ',')
	  s[j] = ' ';	
      }
      stringstream ss; ss << s;
      int a, b;
      ss >> a; --a;
      while(ss >> b) {
	--b;
	COST[a][b] = 1;
	PREV[a][b] = a;
      }
    }
    // Auto fill matrix:
    bool improved = true;
    while(improved) {
      improved = false;
      FORI(M) {
	FORJ(M) {
	  if(i == j)
	    continue;
	  FORK(M) {
	    if(k == i || k == j)
	      continue;
	    if(COST[i][k]+COST[k][j] < COST[i][j]) {
	      improved = true;
	      COST[i][j] = COST[i][k]+COST[k][j];
	      PREV[i][j] = k;
	    }
	  } // FORK
	} // for j
      } // FORI
    } // while(improved)

    /*    
    cerr << " ";
    FORI(M)
      cerr << "  " << i+1;
    cerr << endl;
    FORI(M) {
      cerr << i+1;
      FORJ(M) {
	if(COST[i][j] == INF)
	  cerr << "  X";
	else
	  cerr << "  " << PREV[i][j]+1;
      }
      cerr << endl;
    }//*/
    
    // Handle queries:
    int P; cin >> P;
    FORI(P) {
      int a, b; cin >> a >> b; --a; --b;
      if(COST[a][b] == INF) {
	cout << "connection impossible" << endl;
      }
      else {
	cout << a+1;
	walk(a, b, PREV);
	cout << endl;
      }
    } // FORI(P)
  } // FORCAS
  return 0;
}
