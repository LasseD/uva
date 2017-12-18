bool ok(int &idx, vector<int> &v, int parent, int siblingSum) {
  while(true) {
    if(idx >= (int)v.size())
      return false; // Reading out of boundary :(
    int a = v[idx++];
    if(a == parent)
      return true;
    if(a > 0)
      return false; // Must start with a negative value.
    siblingSum -= a; // positive sum.
    if(siblingSum >= parent)
      return false;
    if(!ok(idx, v, -a, 0))
      return false;
  }
}

int main() {
  string line;
  while(getline(cin, line)) {
    stringstream ss; ss << line;
    vector<int> v;
    int X;
    while(ss >> X) {
      v.push_back(X);
    }
    if(v.empty())
      die(); // WTF!?

    //cerr << "Running for |v|=" << v.size() << endl;

    int idx = 1;
    if(v[0] < 0 && ok(idx, v, -v[0], 0) && idx == (int)v.size()) // Starting with a negative int, read all OK and really did read all.
      cout << ":-) Matrioshka!" << endl;
    else
      cout << ":-( Try again." << endl;
  }
  return 0;
}
