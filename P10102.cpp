int dist(PI a, PI b) {
  return ABS(a.XX-b.XX)+ABS(a.YY-b.YY);
}

int main() {
  int M;
  string s;
  while(cin >> M) {
    vector<PI> ones, threes;
    FORY(M) {
      cin >> s;
      FORX(M) {
	if(s[x] == '1')
	  ones.push_back(PI(x,y));
	else if(s[x] == '3')
	  threes.push_back(PI(x,y));
      }
    }
    int worst = 0;
    FORIT2(vector<PI>, ones) {
      int best = M*M;
      FORIT(vector<PI>, threes) {
	if(dist(*it,*it2) < best)
	  best = dist(*it,*it2);
      }
      if(worst < best)
	worst = best;
    }
    cout << worst << endl;
  }
  return 0;
}
