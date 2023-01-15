int main() {
  vector<int> v;
  int x;
  while(cin >> x) {
    v.push_back(x);
  }
  for(int i = 0; i < (int)v.size()-1; i++) {
    for(int j = i+1; j < (int)v.size(); j++) {
      if(v[i]+v[j] == 2020) {
	cout << "Answer 1: " << (v[i]*v[j]) << endl;
      }
      for(int k = j+1; k < (int)v.size(); k++) {
	if(v[i]+v[j]+v[k] == 2020) {
	  cout << "Answer 2: " << (v[i]*v[j]*v[k]) << endl;
	}
      }
    }
  }
}
