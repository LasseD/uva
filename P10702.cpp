int main() {
  int C, S, E, T, city;
  LL profitMatrix[10000], profit[100], tmpProfit[100];

  while(true) {
    cin >> C >> S >> E >> T;
    if(0 == (C | S | E | T))
      return 0;
    --S;
    // C cities. S start. E ends. T visiting.
    FORI(C) {
      profit[i] = -1; // Indicating no profit.
      FORJ(C) {
	cin >> profitMatrix[i * 100 + j];
      }
    }
    profit[S] = 0;

    // Compute profit:
    FORK(T) { // Walk T times:
      FORJ(C) { // Update each city
	tmpProfit[j] = 0;
	FORI(C) {
	  if(profit[i] == -1)
	    continue;
	  int tryProfit = profit[i] + profitMatrix[i * 100 + j];
	  tmpProfit[j] = MAX(tmpProfit[j], tryProfit);
	}
      }
      FORJ(C) {
	profit[j] = tmpProfit[j];
      }
    } // FORK(T) Walk T times.

    int bestProfit = 0;
    FORI(E) {
      cin >> city; --city;
      if(profit[city] > bestProfit)
	bestProfit = profit[city];
    }
    cout << bestProfit << endl;
  }
}
