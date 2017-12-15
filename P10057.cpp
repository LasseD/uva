int main() {
  int cnt[100000];
  int n, a;
  while(cin >> n) {
    memset(cnt, 0, sizeof(cnt));
    LL sum = 0;
    int max = -1, min = 100000;
    //cerr << endl;
    FORI(n) {
      cin >> a;
      ++cnt[a];
      sum += a;
      max = MAX(max, a);
      min = MIN(min, a);
      //cerr << a << " ";
    }
    //cerr << " => " << endl;

    int bestA = min;
    int cntBestA = 1;
    int cntAInput = cnt[min];
    int left = 0, right = n-cnt[min];
    LL diffLeft = 0, diffRight = sum-n*min;
    LL diffBestA = diffLeft+diffRight;
    left += cnt[min];
    //cerr << "Init: A=" << min << ", bestDiff: " << diffBestA << ", diffRight: " << diffRight << endl;

    for(int i = min+1; i <= max; ++i) {
      diffRight -= right; // Walk one closer.
      diffLeft += left; // Walked one away each.
      //cerr << i << " => " << diffLeft << " + " << diffRight << " = " << diffLeft+diffRight << endl;

      right -= cnt[i]; // Go to limbo.
      if(diffLeft+diffRight < diffBestA) {
	// New best:
	bestA = i;
	cntBestA = 1;
	cntAInput = cnt[i];
	diffBestA = diffLeft+diffRight;
      }
      else if(diffLeft+diffRight == diffBestA) {
	// Update info:
	cntBestA++;
	cntAInput += cnt[i];
      }
      left += cnt[i]; // Out of limbo.
    }

    cout << bestA << " " << cntAInput << " " << cntBestA << endl;
  }
  return 0;
}
