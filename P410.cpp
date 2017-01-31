int main() {
  int chambers, specimens, cas = 1, weights[10];
  while(cin >> chambers >> specimens) {
    printf("Set #%d\n", cas++);
    int sum = 0;
    FORI(specimens) {
      cin >> weights[i];
      sum += weights[i];
    }
    for(int i = specimens; i < 2*chambers; ++i)
      weights[i] = 0;
    sort(weights, weights+2*chambers);
    double avg = sum / (double)chambers;
    double imbalance = 0;

    // Greedy fill best:
    FORI(chambers) {
      // Spool to tmp.
      int a = weights[i];
      int b = weights[chambers*2-i-1];
      imbalance += ABS(a+b-avg);
      printf(" %d:", i);
      if(a != 0)
	printf(" %d", a);
      if(b != 0)
	printf(" %d", b);
      printf("\n");
    }
    printf("IMBALANCE = %.5f\n", imbalance);
    printf("\n");
    
  }
  return 0;
}
