// Add size to start of input.
int *v, size;

LL hashCode() {
  LL ret = 0;
  FORI(size) {
    ret = 19*ret + v[i];
  }
  return ret;
}

int main() {
  cin >> size;
  v = new int[size];
  FORI(size) {
    cin >> v[i];
  }
  map<LL,int> seen;
  int answer = 0;
  LL h;
  while(seen.find(h = hashCode()) == seen.end()) {
    seen[h] = answer;
    // Run round:
    int best = 0;
    for(int i = 1; i < size; i++) {
      if(v[i] > v[best])
	best = i;
    }
    int rem = v[best];
    v[best] = 0;
    for(int i = best+1; rem > 0; i++,rem--) {
      v[i%size]++;
    }
    answer++;
    cout << answer << ":";
    FORI(size)
      cout << " " << v[i];
    cout << endl;
  }
  cout << (-seen[h] + answer) << endl; // Just use answer for Part 1
}
