int main() {
  vector<LL> v;
  LL x;
  while(cin >> x) {
    v.push_back(x);
  }
  cout << "Read " << v.size() << " adaptors" << endl;
  
  v.push_back(0); // outlet
  sort(v.begin(), v.end());
  v.push_back(*v.rbegin() + 3);

  int cnt1 = 0, cnt3 = 0;
  for(int i = 1; i < (int)v.size(); i++) {
    int diff = v[i]-v[i-1];
    if(diff == 1)
      cnt1++;
    else if(diff == 3)
      cnt3++;
  }
  cout << "Answer 1: " << cnt1*cnt3 << endl;

  // Part 2:
  LL *ret = new LL[v.size()];
  ret[0] = 1;
  for(int i = 1; i < (int)v.size(); i++) {
    ret[i] = 0;
    for(int j = i-1; j >= 0; j--) {
      if(v[j]+3 < v[i])
	break;
      ret[i] += ret[j];
    }
  }
  cout << "Answer 2: " << ret[v.size()-1] << endl;
}
