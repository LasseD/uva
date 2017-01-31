int len(int a) {
  int ret = 1;
  while(a > 9) {
    ++ret;
    a/=10;
  }
  return ret;
}

int main() {
  /*
  cerr << "Lens: " << endl;
  FORI(102)
    cerr << i << ": " << len(i) << endl;//*/

  int N, D;
  while(cin >> N >> D) {
    printf("%d/%d = %d.", N, D, N/D);
    int printedDigits = len(N/D);
    int baseN = N = (N%D);
    map<PI,int> m;
    //m.insert(make_pair(PI(N,D), 0));
    int cycleLength, cycleBegin;
    while(true) {
      N = N%D;
      if(m.find(PI(N,D)) != m.end()) {
	//cerr << "Found N=" << N << ", D=" << D << " on position " << m[PI(N,D)] << ", |m|=" << m.size() << endl;	
	cycleBegin = m[PI(N,D)]-1;
	cycleLength = m.size()-cycleBegin;
	//if(cycleLength == 1 && N == 0)
	//++cycleBegin; // Special case.
	break;
      }
      m[PI(N,D)] = (int)m.size();
      N *= 10;
    } 
    // output:
    N = 10*baseN;
    for(int i = 0; i < cycleBegin; ++i) {
      printf("%d", N/D);
      N = N%D;
      N*=10;
      ++printedDigits;
    }
    printf("(");
    for(int i = 0; i < cycleLength; ++i) {
      printf("%d", N/D);
      N = N%D;
      N*=10;
      ++printedDigits;
      if(printedDigits == 51) {
	printf("...");
	break;
      }
    }
    printf(")");
    printf("\n");
    printf("   %d = number of digits in repeating cycle\n\n", cycleLength);
  }
  return 0;
}
