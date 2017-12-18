int main() {
  set<PI> rows[10001];
  int pos[10001];

  int width, height;
  while(cin >> height >> width) {
    FORI(width)
      rows[i].clear();
    FORI(height) {
      GI(N);
      FORJ(N) {
	cin >> pos[j];
	--pos[j];
      }
      FORJ(N) {
	GI(x);
	rows[pos[j]].insert(PI(i, x));
      }
    }
    cout << width << " " << height << endl;
    FORI(width) {
      cout << rows[i].size();
      FORIT(set<PI>, rows[i]) {
	cout << " " << it->first+1;
      }
      cout << endl;
      bool first = true;
      FORIT(set<PI>, rows[i]) {
	if(!first)
	  cout << " ";
	first = false;
	cout << it->second;
      }
      cout << endl;	
    } // FORI
  } // while(cin)
  return 0;
}
