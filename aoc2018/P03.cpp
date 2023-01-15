#define SIZE 1001
// Replace [,:x@#] with space in input
int main() {
  int Q[SIZE][SIZE];
  FORI(SIZE) {
    FORJ(SIZE)
      Q[i][j] = 0;
  }
  
  vector<PI4> v;
  int id, a, b, c, d, miX = 9999, miY = 9999, maX = -999, maY = -999;
  while(cin >> id >> a >> b >> c >> d) {
    v.push_back(PI4(PI(a,b),PI(c,d)));
    miX = min(miX, a);
    miY = min(miY, b);
    maX = max(maX, a+c);
    maY = max(maY, b+d);
    for(int x = a; x < a+c; x++) {
      for(int y = b; y < b+d; y++) {
	Q[y][x]++;
      }
    }
  }
  cout << "Read " << v.size() << " claims, spanning over " << miX << "," << miY << " -> " << maX << "," << maY << endl;
  int answer1 = 0;
  FORI(SIZE) {
    FORJ(SIZE) {
      if(Q[i][j] > 1) {
	answer1++;
      }
    }
  }
  cout << "Answer 1: " << answer1 << endl;
  // Part 2: Find free claim:
  id = 1;
  FORIT(vector<PI4>, v) {
    a = it->first.XX;
    b = it->first.YY;
    c = it->second.XX;
    d = it->second.YY;
    bool ok = true;
    for(int x = a; ok && x < a+c; x++) {
      for(int y = b; y < b+d; y++) {
	if(Q[y][x] != 1) {
	  ok = false;
	  break;
	}
      }
    }
    if(ok) {
      cout << "Answer 2: " << id << endl;
      return 0;
    }
    id++;
  }
}
