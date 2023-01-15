int main() {
  LL sum = 0;
  int x;
  while(cin >> x) {
    x = (x/3)-2;
    while(x > 0) {
      sum += x;
      x = (x/3)-2; // Part 2
    }
  }
  cout << sum << endl;
}
