int main() {
  GI(N);
  map<string,string> m;
  string s1, s2;
  getline(cin, s1);
  
  FORI(N) {
    getline(cin, s1);
    getline(cin, s2);
    m[s1] = s2;
  }

  GI(Q);
  getline(cin, s1);
  FORI(Q) {
    getline(cin, s1);
    cout << m[s1] << endl;
  }
  return 0;
}
