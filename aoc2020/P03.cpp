int main() {
  vector<string> v;
  string s;
  while(cin >> s) {
    v.push_back(s);
  }
  LL answer = 1;
  vector<PI> slopes; // Part 2
  slopes.push_back(PI(1,1));
  slopes.push_back(PI(3,1)); // For part 1, only have this
  slopes.push_back(PI(5,1));
  slopes.push_back(PI(7,1));
  slopes.push_back(PI(1,2));

  FORIT(vector<PI>, slopes) {
    int dx = it->first;
    int dy = it->second;

    PI p(0,0);
    int trees = 0;
    while(p.YY < v.size()) {
      if(v[p.YY][p.XX % v[0].size()] == '#') {
	trees++;
      }
      p.XX+=dx;
      p.YY+=dy;
    }
    answer*=trees;
  }
  cout << "Answer: " << answer << endl;
}
