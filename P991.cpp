int main() {
  int ret[11];
  ret[0] = 1; // 0 paris - 1 way
  ret[1] = 1; // 1 pair - 1 way
  ret[2] = 2; // 2 pairs - 2 ways by following edge of circle
  //ret[3] = 5; // 3 pairs - see problem desc.
  
  for(int i = 3; i <= 10; ++i) {
    int total = i*2;
    // Assume new pair at position 0 and j;
    int sum = 0;
    for(int j = 1; j < total; j+=2) {
      int between0andJ = j-1;
      int betweenJand0 = total - 2 - between0andJ;
      sum += ret[between0andJ/2] * ret[betweenJand0/2];
      //cerr << " i=" << i << ", j=" << j << ": " << ret[between0andJ/2] << "*" << ret[betweenJand0/2] << endl;
    }
    //cerr << i << " pairs: " << sum << endl;
    ret[i] = sum;
  }


  int N;
  bool first = true;
  while(cin >> N) {
    if(!first)
      cout << endl;
    first = false;
    cout << ret[N] << endl;
  }
  return 0;
}
