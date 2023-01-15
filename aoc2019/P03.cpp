typedef map<PI,int> MAP;
MAP s1, s2;

void build(string &line, MAP &S) {
  stringstream ss; ss << line;
  char c;
  int x, steps = 1;
  PI p(0,0);
  while(ss >> c >> x) {
    while(x > 0) {
      switch(c) {
      case 'U':
	p.YY--;
	break;
      case 'D':
	p.YY++;
	break;
      case 'L':
	p.XX--;
	break;
      case 'R':
	p.XX++;
	break;
      }
      if(S.find(p) == S.end())
	S[p] = steps;
      x--;
      steps++;
    }
  }

}

int main() {
  string line;
  getline(cin, line);
  build(line, s1);
  getline(cin, line);
  build(line, s2);
  int answer1 = 9999999;
  int answer2 = 9999999;
  FORIT(MAP, s1) {
    PI p = it->first;
    if(s2.find(p) != s2.end()) {
      int dist = abs(p.XX) + abs(p.YY);
      if(dist > 0) {
	answer1 = min(answer1, dist);

	int d1 = it->second;
	int d2 = s2[p];
	cout << "Intersection " << p.XX << "," << p.YY << " after " << d1 << " and " << d2 << " steps" << endl;
	answer2 = min(answer2, d1+d2);
      }
    }
  }
  cout << answer1 << endl;
  cout << answer2 << endl;
}
