// Replace comma with space in input and remove "turn"
int main() {
  string op, s;
  PI from, to;
  int grid[1000][1000];
  FORI(1000) {
    FORJ(1000) {
      grid[i][j] = 0;
    }
  }
  while(cin >> op >> from.XX >> from.YY >> s >> to.XX >> to.YY) {
    for(int i = from.XX; i <= to.XX; i++) {
      for(int j = from.YY; j <= to.YY; j++) {
	if(op == "on") {
	  grid[i][j]++; // 1 for answer 1
	}
	else if(op == "off") {
	  grid[i][j] = max(0, grid[i][j]-1);	   // 0 for answer 1
	}
	else {
	  grid[i][j] += 2; // !grid[i][j] for answer 1
	}
      }
    }

  }
  LL answer = 0;
  FORI(1000) {
    FORJ(1000) {
      answer += grid[i][j];
    }
  }
  cout << "Answer: " << answer << endl;
}
