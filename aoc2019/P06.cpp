// Replace ) with space in input.
typedef map<string,string> MAP;
int main() {
  MAP m;
  string a, b;
  while(cin >> a >> b) {
    m[b] = a;
  }
  int answer1 = 0;
  FORIT(MAP, m) {
    string planet = it->first;
    answer1++;
    string parent = it->second;
    while(parent != "COM") {
      parent = m[parent];
      answer1++;
    }
  }
  cout << "Answer 1: " << answer1 << endl;

  // Part 2: YOU -> SAN
  map<string,int> dists;
  int dist = 0;
  string you = "YOU";
  while(you != "COM") {
    dists[you] = dist++;
    you = m[you];
  }
  string san = "SAN";
  dist = 0;
  while(dists.find(san) == dists.end()) {
    san = m[san];
    dist++;
  }
  cout << "Answer 2: " << (dist + dists[san] - 2) << endl;
}
