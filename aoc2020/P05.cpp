int main() {
  int answer1 = 0;
  string s;
  set<int> seats;
  while(cin >> s) {
    int miX = 0, maX = 127, miY = 0, maY = 7;
    FORUI(s.size()) {
      char c = s[i];
      if(c == 'B') {
	miX = (maX+miX)/2;
      }
      else if(c == 'F') {
	maX = (maX+miX)/2;
      }
      else if(c == 'R') {
	miY = (maY+miY)/2;
      }
      else if(c == 'L') {
	maY = (maY+miY)/2;
      }
    }
    int id = 8*maX + maY;
    seats.insert(id);
    answer1 = max(answer1, id);
    cout << "X: " << miX << "," << maX << ", Y: " << miY << "," << maY << ", ID: " << id << endl;
  }
  cout << "Answer 1: " << answer1 << endl;
  int last = -1;
  FORIT(set<int>, seats) {
    int id = *it;
    int space = *it - last;
    if(last != -1 && space != 1)
      cout << "Seat ID " << id << " Space: " << space << ", so answer 2 can be: " << id-1 << endl;
    last = id;
  }
}
