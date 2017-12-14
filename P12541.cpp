typedef pair<PI,PI> INFO; // year, month, day, idx

int main() {
  string names[109];
  INFO info[109];
  GI(N);
  FORI(N) {
    cin >> names[i];
    cin >> info[i].P2.P1;
    cin >> info[i].P1.P2;
    cin >> info[i].P1.P1;
    info[i].P2.P2 = i;
  }
  sort(info, info+N);
  cout << names[info[N-1].P2.P2] << endl;
  cout << names[info[0].P2.P2] << endl;
}
