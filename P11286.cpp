int main() {
  while(true) {
    int N; cin >> N;
    if(N == 0)
      return 0;
    map<ULL,int> m;
    int max = 1;
    FORI(N) {
      ULL courses = 0;
      int c[5];
      FORJ(5) {
	cin >> c[j];
      }
      sort(c, c+5);
      FORJ(5) {
	courses = 500*courses+c[j];
      }
      map<ULL,int>::iterator it = m.find(courses);
      if(it == m.end()) {
	m.insert(make_pair(courses,1));
	//cerr << "New config: " << courses << endl;
      }
      else {
	++it->second;
	max = MAX(max, it->second);
	//cerr << "config: " << courses << " => " << it->second << endl;
      }      
    }
    int ret = 0;
    for(map<ULL,int>::iterator it = m.begin(); it != m.end(); ++it) {
      if(it->second == max)
	ret += max;
    }
    cout << ret << endl;
  }
}
