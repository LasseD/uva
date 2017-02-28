int main() {
  int duration, depreciationRecords;
  double downPayment, loanAmount, depreciation[101];
  while(true) {
    cin >> duration >> downPayment >> loanAmount >> depreciationRecords;
    if(duration < 0)
      return 0;
    memset(depreciation, -1, 101*sizeof(double));
    FORI(depreciationRecords) {
      int idx;
      cin >> idx;
      cin >> depreciation[idx];
    }
    double dep = depreciation[0];
    double value = (downPayment + loanAmount)*(1-dep);
    double owed = loanAmount;
    int ret = 0;
    while(owed >= value) {
      ++ret;
      if(depreciation[ret] >= 0)
	dep = depreciation[ret];
      value *= (1-dep);
      owed = loanAmount * (duration-ret)/(double)duration;
    }
    cout << ret << " month";
    if(ret != 1)
      cout << "s";
    cout << endl;
  }
}
