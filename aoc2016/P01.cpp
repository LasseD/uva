// Input cleanup: Remove "," and add space after each L and R
int main() {
  PI p(0,0);
  int dir = 0;
  string s;
  set<PI> S;
  S.insert(p);
  
  while(cin >> s) {
    if(s[0] == 'L')
      dir = (dir+3)%4;
    else
      dir = (dir+1)%4;
    GI(dist);
    FORI(dist) {
      switch(dir) {
      case 0:
	p.XX++;
	break;
      case 1:
	p.YY++;
	break;
      case 2:
	p.XX--;
	break;
      case 3:
	p.YY--;
	break;
      }
      if(S.find(p) != S.end()) {
	cout << "Answer 2: " << (abs(p.XX)+abs(p.YY)) << endl;
      }
      else
	S.insert(p);
    }
  }
  cout << "Answer 1: " << (abs(p.XX)+abs(p.YY)) << endl;
}
