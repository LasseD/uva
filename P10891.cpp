int main() {
  int N, a[101][100]; // size 1..100, start 0..99
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    FORI(N) {
      cin >> a[0][i];
      //cerr << a[0][i] << " ";
    }
    //cerr << endl;
    for(int size = 2; size <= N; ++size) {
      for(int pos = 0; pos + size <= N; ++pos) {
	// Best is first taking all!
	int best = 0;
	FORI(size)
	  best += a[0][pos+i];

	// Try to improve best:
	int fromLeft = 0;
	for(int left = 1; left < size; ++left) {
	  fromLeft += a[0][pos+left-1];
	  int newScore = fromLeft - a[size-left-1][pos+left];
	  if(newScore > best) {
	    //cerr << "<";
	    best = newScore;
	  }
	}
	// Again from right:
	int fromRight = 0;
	for(int right = 1; right < size; ++right) {
	  fromRight += a[0][size+pos-right];
	  int newScore = fromRight - a[size-right-1][pos];
	  if(newScore > best) {
	    //cerr << ">";
	    best = newScore;
	  }
	}
	a[size-1][pos] = best;
	//cerr << best << " ";
      } // for pos
      //cerr << endl;
    } // for size
    cout << a[N-1][0] << endl;
  } // while(true)
} // int main
