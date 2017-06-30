/*
OK. Let's try to improve this: Improce the computation of tmpProfit.

Attempt 1:
Stop early by sorting and using "highestProfitGoingToCity" and "sortedCities".
=> Time from 0.030 -> 0.010 (Only 6 others here. None at 0.000).

Attempt 2: 
Only update profit(key) in "sortedCities" => less "sorting" in each step.

 */
int main() {
  int C, S, E, T, city;
  int profitMatrix[100][100], profit[100], tmpProfit[100], highestProfitGoingToCity[100];
  PI sortedCities[100]; // value -> city

  while(true) {
    scanf("%d %d %d %d", &C, &S, &E, &T);
    if(0 == (C | S | E | T))
      return 0;
    --S;
    FORI(C) {
      sortedCities[i] = PI(-1000000000, i);
      highestProfitGoingToCity[i] = 0;
    }
    sortedCities[S] = PI(0, S);

    // C cities. S start. E ends. T visiting.
    FORI(C) {
      profit[i] = -1000000000; // Indicating no profit.
      FORJ(C) {
	scanf("%d", &profitMatrix[j][i]);
	if(profitMatrix[j][i] > highestProfitGoingToCity[j])
	  highestProfitGoingToCity[j] = profitMatrix[j][i];
      }
    }
    profit[S] = 0;

    // Compute profit:
    FORK(T) { // Walk T times:
      sort(sortedCities, sortedCities+C);

      FORJ(C) { // Update each city
	tmpProfit[j] = 0;
	for(int xi = C-1; xi >= 0 && tmpProfit[j] < sortedCities[xi].first + highestProfitGoingToCity[j]; --xi) {
	  int i = sortedCities[xi].second;
	  int tryProfit = profit[i] + profitMatrix[j][i];
	  if(tryProfit > tmpProfit[j])
	    tmpProfit[j] = tryProfit;
	}
      }
      swap(profit, tmpProfit);

      FORJ(C) {
	sortedCities[j].first = profit[sortedCities[j].second];
      }
    } // FORK(T) Walk T times

    int bestProfit = 0;
    FORI(E) {
      scanf("%d", &city);
      --city;
      if(profit[city] > bestProfit)
	bestProfit = profit[city];
    }
    printf("%d\n", bestProfit);
  }
}
