int main() {
  ULL n;
  while(true) {
    cin >> n;
    if(n == 0)
      return 0;
    vector<int> IS;
    FORI(32) {
      if(1 == (n & 1))
	IS.push_back(i);
      n >>= 1;
    }
    // Build A and B: 
    ULL A = 0, B = 0;
    FORUI(IS.size()) {
      if(i % 2 == 0) {
	A += 1 << IS[i];
      }
      else {
	B += 1 << IS[i];
      }
    }
    cout << A << " " << B << endl;
  }
}
