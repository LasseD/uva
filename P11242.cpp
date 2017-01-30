int main() {
  int f, r, front[10], rear[10];
  while(true) {
    cin >> f;
    if(f == 0)
      return 0;
    cin >> r;
    FORI(f)
      cin >> front[i];
    FORI(r)
      cin >> rear[i];
    vector<double> ratios;
    FORI(f) {
      FORJ(r) {
	ratios.push_back(rear[j]/(double)front[i]);
      }
    }
    sort(ratios.begin(), ratios.end());
    double best = 0;
    FORUI(ratios.size()) {
      if(i == 0)
	continue;
      double d = ABS(ratios[i]/ratios[i-1]);
      if(d > best)
	best = d;
    }
    printf("%.2f\n", best);
  }
}
