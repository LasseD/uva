#define INF 999999

int main() {
  int COST[31][31];
  cout << "SHIPPING ROUTES OUTPUT" << endl << endl;

  FORCAS {
    cout << "DATA SET  " << (cas+1) << endl << endl;

    int M, N, P; cin >> M >> N >> P; // M=|warehouses|, N=|edges|, P=|queries|
    //cerr << "M=" << M << ", N=" << N << ", P=" << P << endl;
    map<string,int> warehouses;
    // Read warehouses:
    FORI(M) {
      string s; cin >> s;
      warehouses.insert(make_pair(s,(int)warehouses.size()));
      //cerr << " " << s;
    }
    //cerr << endl;
    // Set adjacency matrix:
    FORI(M) {
      FORJ(M) {
	COST[i][j] = INF;
      }
    }
    FORI(M) {
      COST[i][i] = 0;
    }
    FORI(N) {
      string sa, sb; cin >> sa >> sb;
      int a = warehouses[sa];
      int b = warehouses[sb];
      COST[a][b] = COST[b][a] = 1;
      //cerr << sa << "->" << sb << ": " << a << "->" << b << endl;
    }
    // Auto fill matrix:
    bool improved = true;
    while(improved) {
      improved = false;
      FORI(M) {
	for(int j = i+1; j < M; ++j) {
	  FORK(M) {
	    if(k == i || k == j)
	      continue;
	    if(COST[i][k]+COST[k][j] < COST[i][j]) {
	      improved = true;
	      COST[i][j] = COST[j][i] = COST[i][k]+COST[k][j];
	    }
	  } // FORK
	} // for j
      } // FORI
    } // while(improved)

    /*
    FORI(M) {
      FORJ(M) {
	if(COST[i][j] == INF)
	  cerr << "  X";
	else
	  cerr << "  " << COST[i][j];
      }
      cerr << endl;
    }//*/

    
    // Handle queries:
    FORI(P) {
      int size; cin >> size;
      string sa, sb; cin >> sa >> sb;
      int a = warehouses[sa];
      int b = warehouses[sb];
      if(COST[a][b] == INF) {
	cout << "NO SHIPMENT POSSIBLE" << endl;
      }
      else {
	cout << "$" << (COST[a][b]*100*size) << endl;
      }
    } // FORI(P)
    cout << endl;
  } // FORCAS
  cout << "END OF OUTPUT" << endl;
  return 0;
}
