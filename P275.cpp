int main() {
  int N, D;
  while(true) {
    cin >> N >> D;
    if(N == 0 && D == 0) return 0;
    //cout << N << "/" << D << " = ";
    printf(".");
    
    map<int,int> m; // remainder(N is used for this) -> first seen.
    m[N] = 0; // The remainder N is seen at position 0 because N < D.
    for(int pos = 1; true; ++pos) {
      N *= 10;
      int digit = N/D;
      N %= D;
      if(m.find(N) != m.end()) {
	int cycleLength = pos-m[N]-1;
	if(cycleLength == 0 && digit == 0)
	  printf("\nThis expansion terminates.\n\n");
	else {
	  if(pos % 50 == 0)
	    printf("\n");
	  printf("%d", digit);
	  printf("\nThe last %d digits repeat forever.\n\n", cycleLength+1);
	}
	break;
      }
      m[N] = pos;

      if(pos % 50 == 0)
	printf("\n");
      printf("%d", digit);

    }
  }
}
