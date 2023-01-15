int acc;
vector<PSI> v;

bool halts() {
  int idx = 0;
  acc = 0;
  set<int> seen;

  while(idx < (int)v.size()) {
    if(seen.find(idx) != seen.end()) {
      return false;
    }
    seen.insert(idx);
    string op = v[idx].first;
    int val = v[idx].second;
    if(op == "nop") {
      idx++;
    }
    else if(op == "acc") {
      acc += val;
      idx++;
    }
    else if(op == "jmp") {
      idx += val;
    }
  }
  return true;
}

int main() {
  string op;
  int val;
  while(cin >> op >> val) {
    v.push_back(PSI(op,val));
  }

  // For part run, just run halts and output acc.
  halts();
  cout << "Answer 1: " << acc << endl;
  
  // Part 2:
  FORUI(v.size()) {
    if(v[i].first == "acc")
      continue; // acc is ok
    if(v[i].first == "nop") {
      v[i].first = "jmp";
      if(halts()) {
	cout << "Answer 2: " << acc << endl;
	return 0;
      }
      v[i].first = "nop";
    }
    else { // is jmp
      v[i].first = "nop";
      if(halts()) {
	cout << "Answer 2: " << acc << endl;
	return 0;
      }
      v[i].first = "jmp";
    }
  }
}
