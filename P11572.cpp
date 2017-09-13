int main() {
  FORCAS {
    int n;
    cin >> n;
    
    int *a = new int[n];
    unsigned int best = 0;
    int start = 0;
    set<int> s; // Current package.
    
    FORI(n) {
      cin >> a[i];
      if(s.find(a[i]) == s.end()) {
	s.insert(a[i]);
	if(s.size() > best)
	  best = s.size();	
      }
      else {
	while(a[start] != a[i])
	  s.erase(a[start++]);
	++start;
      }
    }
    cout << best << endl;
    
    delete[] a;
  }
}
