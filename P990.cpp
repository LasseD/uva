int main() {
  int time, w, treasures, sizes[30], depths[30], best[31][1001];
  bool first = true;
  while(cin >> time >> w >> treasures) {
    if(!first)
      cout << endl;
    first = false;
    FORI(time+1)
      best[0][i] = 0; // No treasures {}.

    FORI(treasures) { // Try to add treasure i:
      FORJ(time+1)
	best[i+1][j] = best[i][j]; // Same as without this treasure.

      cin >> depths[i] >> sizes[i];
      for(int j = time; j >= 3*w*depths[i]; --j) {
	if(sizes[i]+best[i][j-3*w*depths[i]] > best[i][j]) {
	  best[i+1][j] = sizes[i]+best[i][j-3*w*depths[i]];
	}
      }
    }

    // Backtrack to output:
    stack<int> s;
    cout << best[treasures][time] << endl;
    int backtrackTime = time;
    for(int i = treasures; i > 0; --i) {
      if(best[i][backtrackTime] != best[i-1][backtrackTime]) {
	s.push(i-1);
	backtrackTime -= 3*w*depths[i-1];
      }
    }
    cout << s.size() << endl;
    while(!s.empty()) {
      cout << depths[s.top()] << " " << sizes[s.top()] << endl;
      s.pop();
    }
  }
  return 0;
}
