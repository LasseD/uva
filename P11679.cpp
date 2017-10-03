int owed[20][20]; // owed[i][j] => Bank i+1 owes i+j amount
int totalOwed[20]; // [i] => Bank i+1 owes in total
int reserves[20];
bool visited[20];
int B;

bool removeCycleDfs(int start, int cur, int &minLink) {
  if(cur == start) {
    //cerr << "Cycle found from " << start << " of min price " << minLink << endl; 
    return true;
  }
  visited[cur] = true;
  int oldMinLink = minLink;
  FORJ(B) {
    if(visited[j])
      continue;
    minLink = oldMinLink;
    if(owed[cur][j] > 0) {
      if(owed[cur][j] < minLink)
	minLink = owed[cur][j];
      if(removeCycleDfs(start, j, minLink)) {
	totalOwed[cur] -= minLink;
	owed[cur][j] -= minLink;
	// Note: Reserves stay unchanged!
	visited[cur] = false;
	//cerr << " Cycle reduction " << cur << "->" << j << " remaining: " << owed[cur][j] << endl;
	return true;
      }
    }
  }
  visited[cur] = false;
  return false;
}

void removeCyclesFrom(int start) {
  FORJ(B) { // Try to find cycles by first going to all neighbours
    if(j == start)
      continue;
    
    while(owed[start][j] > 0) {
      int minLink = owed[start][j];
      if(!removeCycleDfs(start, j, minLink))
	break;
      totalOwed[start] -= minLink;
      owed[start][j] -= minLink;
      //      cerr << " Cycle reduction " << start << "=>" << j << " remaining: " << owed[start][j] << endl;
    }
  }
}

// OK. So apaprently banks don't need to have money to spend money... confusing problem definition. Ignore the methods above.
int main() {
  int N, from, to, amount; // Banks, debentures
  while(true) {
    cin >> B >> N;
    if(B == 0 && N == 0)
      return 0;
    FORI(B) {
      FORJ(B)
	owed[i][j] = 0;
      totalOwed[i] = 0;
      visited[i] = false;
      cin >> reserves[i];
    }
    FORI(N) {
      cin >> from >> to >> amount; --from; --to;
      if(from == to)
	continue;
      owed[from][to] += amount;
      totalOwed[from] += amount;
      reserves[from] -=amount;
      reserves[to] += amount;
    }

    /*
    // Remove cycles
    FORI(B) {
      if(reserves[i] != 0)
	removeCyclesFrom(i);
    }
    
    // Fix rest greedily:
    bool improved = true;
    while(improved) {
      improved = false;
      FORI(B) { // Try to improve all banks
	if(reserves[i] == 0 || totalOwed[i] == 0)
	  continue;
	improved = true;
	// Try to pay off debt:
	FORJ(B && reserves[i] > 0) {
	  if(owed[i][j] == 0)
	    continue;
	  int pay = MIN(owed[i][j], reserves[i]);
	  owed[i][j] -= pay;
	  reserves[i] -= pay;
	  reserves[j] += pay;
	  totalOwed[i] -= pay;
	  //cerr << "Normal payment " << i << "->" << j << ": " << pay << ". Remaining: " << owed[i][j] << endl;
	} // FORJ
      } // FORI
    } // while improved
*/
    char ret = 'S';
    FORI(B) {
      if(reserves[i] < 0) {
	ret = 'N';
	break;
      }
    }
    cout << ret << endl;
    
  } // while true
}
