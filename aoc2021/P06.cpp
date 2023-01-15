int main() {
  ULL v[9];  FORI(9) v[i] = 0;
  int x;
  while(cin >> x) {
    v[x]++;
  }
  FORI(256) { // Simulate 80 days in part 1
    LL zeros = v[0];
    for(int j = 0; j < 9; j++) {
      v[j-1] = v[j];
    }
    // Add for zeros:
    v[6]+= zeros;
    v[8] = zeros;
  }
  LL sum = 0;
  FORI(9)
    sum += v[i];
  cout << sum << endl;
}
