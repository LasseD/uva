int main() {
  LL v[2000];
  int size = 0;
  while(cin >> v[size]) {
    size++;
  }
  int idx = 0, steps = 0;
  while(idx >= 0 && idx < size) {
    int next = idx + v[idx];
    if(v[idx] >= 3)
      v[idx]--; // Only part 2
    else
      v[idx]++;
    idx = next;
    steps++;
  }
  cout << steps << endl;
}
