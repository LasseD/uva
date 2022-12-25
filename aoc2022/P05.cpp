// Replaced empty spots with "." and added stack info in top of input.
int main() {
  GI(S); // Number of stacks
  GI(H); // Initial height
  stack<char> stacks[10];
  stack<char> buffers[10];

  FORI(H) {
    FORJ(S) {
      GS(x);
      if(x[0] != '.') {
	buffers[j].push(x[1]);
	cout << x[1];
      }
      else {
	cout << x;
      }
    }
    cout << endl;
  }
  FORI(S) {
    while(!buffers[i].empty()) {
      char c = buffers[i].top();
      buffers[i].pop();
      stacks[i].push(c);
    }
  }
  FORI(S) {
    GI(ignore);
    cout << stacks[i].size() << " ";
  }
  cout << endl;

  string ignore;
  int move, from, to;
  stack<char> tmp;
  while(cin >> ignore >> move >> ignore >> from >> ignore >> to) {
    FORI(move) {
      char c = stacks[from-1].top();
      stacks[from-1].pop();
      tmp.push(c); // For problem 1, simply dump directly into to-stack
    }
    FORI(move) {
      char c = tmp.top();
      tmp.pop();
      stacks[to-1].push(c);
    }
  }
  FORI(S) {
    cout << stacks[i].top();
  }
  cout << endl;

} // int main
