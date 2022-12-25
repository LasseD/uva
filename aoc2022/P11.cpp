struct Monkey {
  vector<LL> items;
  bool opPlus;
  LL right,test,t,f; // right 0 means use old
  int inspections;
};

Monkey monkeys[8];

int main() {
  // Parse input:
  string s;
  int size = 0;
  LL supermod = 1;
  while(cin >> s >> s >> s >> s) { // Monkey <?>: starting items:
    vector<string> v;
    Monkey &m = monkeys[size];
    while(cin >> s && s != "Operation:") {
      LL x = 10*(s[0]-'0') + (s[1]-'0');
      m.items.push_back(x);
    }
    cin >> s >> s >> s >> s; // new = old <op>
    m.opPlus = s == "+";
    cin >> s; // <right>
    m.right = s == "old" ? 0 : stoi(s);
    cin >> s >> s >> s >> m.test; // Test: divisible by <test>
    cin >> s >> s >> s >> s >> s >> m.t; // If true: throw to monkey <t>
    cin >> s >> s >> s >> s >> s >> m.f; // If false: throw to monkey <f>    
    m.inspections = 0;
    supermod*=m.test;
    size++;
  }

  // Simulate rounds:
  FORI(10000) { // For answer 1, use 20 here
    FORJ(size) {
      Monkey &m = monkeys[j];
      FORIT(vector<LL>,m.items) {
	LL item = *it;
	// OP:
	LL right = m.right == 0 ? item : m.right;
	item = m.opPlus ? (item + right) : (item * right);
	//item /= 3; For answer 1, use this.
	item = item % supermod;

	if(item % m.test == 0)
	  monkeys[m.t].items.push_back(item);
	else
	  monkeys[m.f].items.push_back(item);
	m.inspections++;
      }
      m.items.clear();
    }
    // Status:
    cout << "After round " << (i+1) << ", the monkeys are holding items with these worry levels:" << endl;
    FORJ(size) {
      cout << "Monkey " << j << ":";
      Monkey &m = monkeys[j];
      FORIT(vector<LL>,m.items) {
	cout << " " << *it;
      }
      cout << endl;
    } //*/
  }

  // Find monkey business:
  vector<LL> w;
  FORI(size) {
    w.push_back(monkeys[i].inspections);
  }
  sort(w.rbegin(), w.rend());
  cout << "Answer 1: " << (w[0]*w[1]) << endl;
  // And remember to submit the answer from the test input, not the sample input... otherwise you have to wait a minute ;(
}
