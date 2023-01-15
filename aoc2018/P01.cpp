// RM + from input
int main() {
  LL a = 0, b;
  set<LL> s;
  vector<LL> v;
  while(cin >> b) {
    v.push_back(b);
  }
  cout << "Read " << v.size() << " changes" << endl;
  for(int i = 0; true; i++) {
    b = v[i%v.size()];
    a += b;
    if(s.find(a) != s.end()) {
      cout << "Answer 2: " << a << endl;
      return 0; // Part 2 only
    }
    s.insert(a);
  }
  //cout << a << endl; // Part 1 only
}
