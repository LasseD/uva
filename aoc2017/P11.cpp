int dist(PI p) {
  // Get back to 0,0:
  int ret = 0;
  int dirX = p.XX > 0 ? -1 : 1;
  while(p.XX != 0) {
    if(p.XX % 2 == 0) {
      if(p.YY > 0)
	p.YY--;
    }
    else {
      if(p.YY < 0)
	p.YY++;
    }
    p.XX+=dirX;
    ret++;
  }
  ret += abs(p.YY);
  return ret;
}

// Replace comma with space in input.
int main() {
  PI p(0,0);
  string s;
  int answer2 = -1;
  while(cin >> s) {
    if(s == "s") {
      p.YY++;
      continue;
    }
    if(s == "n") {
      p.YY--;
      continue;
    }
    
    if(p.XX % 2 == 0) {
      if(s[0] == 'n')
	p.YY--;
    }
    else {
      if(s[0] == 's')
	p.YY++;
    }
    if(s[1] == 'e')
      p.XX--;
    else // w:
      p.XX++;
    answer2 = max(answer2, dist(p));
  }
  
  cout << "Answer 1: " << dist(p) << endl;
  cout << "Answer 2: " << answer2 << endl;
}
