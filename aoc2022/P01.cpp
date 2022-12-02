int main() {
  int calories = 0;
  vector<int> all;

  string w;
  while(getline(cin, w)) {
    if(w == "") {
      all.push_back(calories);
      calories = 0;
    }
    else {
      calories += stoi(w);
    }
  }
  // Last elve:
  all.push_back(calories);

  sort(all.rbegin(), all.rend());

  int sum = 0;
  FORI(3) {
    sum += all[i];
  }
     
  cout << sum << endl;
} // int main
