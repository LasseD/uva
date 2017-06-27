void addEdge(int i, int j, vector<PI> &critical) {
  if(i > j)
    swap(i, j);
  critical.push_back(PI(i, j));
}

int findAllCritical(int from, int nodeIndex, bool *self, bool *visited, int *marked, vector<int> *E, vector<PI> &critical) {
  visited[nodeIndex] = self[nodeIndex] = true;

  int sumBelow = 0;

  // Visit all that are connected:
  FORIT(vector<int>, E[nodeIndex]) {
    if(*it == from)
      continue; // No single edge "loop".

    //cerr << "Visiting " << nodeIndex << "->" << *it << endl;
    if(self[*it]) {
      ++marked[*it];
      sumBelow++;
      //cerr << " Marked " << *it << ". Sum=" << sumBelow << endl;
    }
    else {
      if(visited[*it])
	continue;

      int add = findAllCritical(nodeIndex, *it, self, visited, marked, E, critical);
      if(add == 0)
	addEdge(nodeIndex, *it, critical);
      sumBelow += add;
      //cerr << nodeIndex << "->" << *it << " visited. add=" << add << ", Sum=" << sumBelow << endl;
    }
  }

  self[nodeIndex] = false;
  return sumBelow - marked[nodeIndex];
}

int main() {
  string w;
  int N, n1, n2;
  
  for(int cas = 0; true; ++cas) {
    if(!(cin >> N))
      return 0;

    vector<int> *E = new vector<int>[N];
    FORK(N) {
      cin >> n1 >> w;
      E[n1].clear();
      int neighbours = 0;
      for(unsigned int j = 1; isdigit(w[j]); ++j)
	neighbours = 10*neighbours + w[j]-'0';
      FORJ(neighbours) {
	cin >> n2;
	E[n1].push_back(n2);
	//cerr << "Edge " << n1 << "->" << n2 << endl;
      }
    }

    vector<PI> critical;
    bool *visited = new bool[N], *self = new bool[N];
    int *marked = new int[N];
    
    FORI(N) {
      visited[i] = self[i] = false;
      marked[i] = 0;
    }

    FORI(N) {
      if(!visited[i]) {
	findAllCritical(-1, i, self, visited, marked, E, critical);
      }
    }
    sort(critical.begin(), critical.end());
    cout << critical.size() << " critical links" << endl;
    FORIT(vector<PI>, critical)
      cout << it->first << " - " << it->second << endl;
    cout << endl;
    
    delete[] E;
    delete[] visited;
    delete[] marked;
    delete[] self;
  } // while(true)
} // main
