#define SIZE 56

// Input cleanupt: Remove "has flow rate=", "; tunnels lead to valve(s)", ","
struct Valve {
  int flow;
  string name;
  vector<string> neighbours;
};

int dist[SIZE][SIZE];
int flow[SIZE];
int path[SIZE];
int size;
vector<string> names;

// Upper bound on how much value is left in network.
int ideal(int pos, int time) {
  int ret = 0;
  FORI(size) {
    int add = flow[i] * (time-1-dist[pos][i]);
    if(add > 0)
      ret += add;
  }
  return ret;
}
int ideal2(int p1, int p2, int time1, int time2) {
  int ret = 0;
  FORI(size) {
    int add = flow[i] * max(time1-1-dist[p1][i],time2-1-dist[p2][i]);
    if(add > 0)
      ret += add;
  }
  return ret;
}

// At pos, time
int go(int pos, int time, int depth) {
  if(time <= 0)
    return 0;
  time--;
  int ret = flow[pos] * time;
  int tmp = flow[pos];
  flow[pos] = 0;

  int best = 0, bestI = 0;
  FORI(size) {
    if(flow[i] == 0)
      continue; // No need to go there
    int timeThere = time-dist[pos][i];
    if(ideal(i, timeThere) < best)
      continue; // Can't improve
    int test = go(i, timeThere, depth+1);
    if(test > best) {
      best = test;
      bestI = i;
    }
  }
  
  path[depth] = bestI;
  if(best > 0)
    go(bestI, time-dist[pos][bestI], depth+1);

  flow[pos] = tmp; // Restore flow.
  return ret + best;
}

int go2(int pos1, int pos2, int time1, int time2, int depth, int current, int &bestEver) {
  int best = 0;
  FORI(size) {
    if(flow[i] == 0)
      continue; // No need to go there
    int tmp = flow[i];
    flow[i] = 0;

    path[depth] = i;
    if(time1 > dist[pos1][i]+1) { // Try 1:
      int timeThere = time1-1-dist[pos1][i];
      int add = tmp*timeThere;
      if(ideal2(i, pos2, timeThere, time2) > best-add) {
	int test = add+go2(i, pos2, timeThere, time2, depth+1, current+add, bestEver);
	if(test > best) {
	  best = test;
	}
      }
    }
    if(time2 > dist[pos2][i]+1) { // Try 2:
      int timeThere = time2-1-dist[pos2][i];
      int add = tmp*timeThere;
      if(ideal2(pos1, i, time1, timeThere) > best-add) {
	int test = add+go2(pos1, i, time1, timeThere, depth+1, current+add, bestEver);
	if(test > best) {
	  best = test;
	}
      }
    }

    if(best + current > bestEver) {
      bestEver = best+current;
      cout << "New best: " << bestEver << ":";
      FORJ(depth) {
	cout << " " << names[path[j]];
      }
      cout << endl;      
    }

    flow[i] = tmp;
  }
  return best;
}

int main() {
  map<string,int> indices; // name -> index
  indices["AA"] = 0;
  names.push_back("AA");
  
  FORI(SIZE) {
    FORJ(SIZE) {
      dist[i][j] = 9999;
    }
    dist[i][i] = 0;
  }
  
  map<string,Valve*> m;
  string line;
  int withFlow = 0;
  size = 0;
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    Valve *v = new Valve;
    string s;
    ss >> s >> v->name >> v->flow;    
    if(indices.find(v->name) == indices.end()) {
      indices[v->name] = (int)indices.size();
      names.push_back(v->name);
    }
    int a = indices[v->name];
    flow[a] = v->flow;
    while(ss >> s) {
      v->neighbours.push_back(s);
      if(indices.find(s) == indices.end()) {
	indices[s] = (int)indices.size();
	names.push_back(s);
      }
      int b = indices[s];
      dist[a][b] = dist[b][a] = 1;
    }
    m[v->name] = v;
    if(v->flow > 0) {
      withFlow++;
      cout << withFlow << " " << v->name << ": " << v->flow << endl;
    }
    size++;
  }

  // Update dist map:
  bool updated = true;
  while(updated) {
    updated = false;
    FORI(size) {
      FORJ(size) {
	FORK(size) {
	  if(dist[i][j] > dist[i][k]+dist[k][j]) {
	    dist[i][j] = dist[i][k]+dist[k][j];
	    updated = true;
	  }
	}
      }
    }
  }
  FORI(size) {
    FORJ(size) {
      int d = dist[i][j];
      if(d < 10)
	cout << " ";
      cout << " " << d;	
    }
    cout << endl;
  }//*/
  
  FORI(size)
    path[i] = 0;
  cout << "Answer 1: " << go(0, 31, 0) << endl;
  FORI(size) {
    if(path[i] == 0)
      break;
    cout << " " << names[path[i]];
  }
  cout << endl;

  // Task 2:
  int bestEver;
  cout << "Answer 2 to be computed below:"<<endl;
  go2(0, 0, 26, 26, 0, 0, bestEver);
  cout << "Done" << endl;
}
