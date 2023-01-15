int capacity[100], answer = 0, N = 0, inUse[100], shortest = 1000;

void go(int remaining, int idx, int len) {
  if(0 == remaining) {
    cout << "Combination " << answer << " of length " << len << ":";
    FORI(len) {
      cout << " " << inUse[i] << "(" << capacity[inUse[i]] << ")";
    }
    cout << endl;
    if(len < shortest) {
      answer = 0;
      shortest = len;
    }
    if(len == shortest) {
      answer++;
    }
    return;
  }
  if(idx == N) {
    return; // No more cups.
  }
  /*if(capacity[idx] > remaining) {    
    return; // Can't fill. Skip.
  }*/
  //cout << "Try cup " << idx << " of size " << capacity[idx] << ", remaining: " << remaining << endl;

  // Try next cup:
  if(idx+1 <= N) {
    if(remaining >= capacity[idx]) {
      inUse[len] = idx;
      go(remaining-capacity[idx], idx+1, len+1); // Use the cup
    }
    go(remaining, idx+1, len); // Skip the cup
  }
}

int main() {
  GI(CAP);
  while(cin >> capacity[N]) {
    N++;
  }
  cout << "Elves have " << CAP << " liters. There are " << N << " cups" << endl;
  //sort(capacity, capacity+N);
  FORI(N) {
    cout << " " << capacity[i];
  }
  cout << endl;

  go(CAP, 0, 0);

  cout << "Answer: " << answer << endl;
}
