#define INF 1000000000000

int main() {
  int n, k; 
  long long costToCity[11];
  vector<long long> prices[11][11];

  for(int cas = 1; true; ++cas) {
    cin >> n >> k; // n cities s=1..n=t, k days.
    if(n == 0 && k == 0)
      return 0;
    
    FORI(n)
      costToCity[i] = INF;
    costToCity[n-1] = 0; // Last day we must be in Atlanta.
    
    // Read fares:
    FORI(n) {
      FORJ(n) {
	prices[i][j].clear();
	if(i == j)
	  continue;
	int len;
	cin >> len;
	//cerr << i << "->" << j << ":";
	FORK(len) {
	  long long price;
	  cin >> price;
	  //cerr << " " << price;
	  prices[i][j].push_back(price);
	}
	//cerr << endl;
      }
    }

    // Walk backwards in time:
    for(int day = k-1; day >= 0; --day) {
      long long newCostToCity[11];
      FORI(n) { // Go to Atlanta from this destination at day:
	long long best = INF;
	FORJ(n) {
	  if(i == j || prices[i][j].empty())
	    continue;
	  long long price = prices[i][j][day % prices[i][j].size()];
	  if(price == 0)
	    continue;
	  if(price + costToCity[j] < best) {
	    best = price + costToCity[j];
	  }
	}
	newCostToCity[i] = best;
      }
      FORI(n) {
	costToCity[i] = newCostToCity[i];
	//cerr << " " << costToCity[i];
      }
      // cerr << endl;
    }
    
    cout << "Scenario #" << cas << endl;
    if(costToCity[0] == INF) {
      cout << "No flight possible." << endl;
    }
    else {
      cout << "The best flight costs " << costToCity[0] << "." << endl;
    }
    cout << endl;
  } // for cas
} // int main
