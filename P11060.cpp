int main() {
  int N, M, a1, a2, indegree[100];
  string s, b1, b2;
  bool done[100];

  for(int cas = 1; cin >> N; ++cas) {
    map<string,int> m; // name -> index  
    vector<string> names(N);
    vector<vector<int> > out(N);
    FORI(N) {
      cin >> names[i];
      m[names[i]] = i;
    }
    memset(indegree, 0, sizeof(indegree));
    memset(done, false, sizeof(done));

    cin >> M;
    FORI(M) {
      cin >> b1 >> b2;
      a1 = m[b1];
      a2 = m[b2];
      out[a1].push_back(a2);
      ++indegree[a2];
    }
    
    cout << "Case #" << cas << ": Dilbert should drink beverages in this order:";
    int printed = 0;
    while(printed < N) {
      FORI(N) {
	if(done[i] || indegree[i] > 0)
	  continue;
	cout << " " << names[i];
	done[i] = true;
	++printed;
	FORIT(vector<int>, out[i]) {
	  --indegree[*it];
	}
	break;
      }
    }
    cout << "." << endl << endl;
  }
  return 0;
}
