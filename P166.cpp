int main() {
  int coins[6] = {5, 10, 20, 50, 100, 200};
  FORI(6)
    coins[i]/=5;

  // Precompute amount of coins that change hand for all over-pays:
  int overpay[101];
  FORI(101)
    overpay[i] = 99999;
  overpay[0] = 0;

  for(int coinI = 5; coinI >= 0; --coinI) {
    int coin = coins[coinI];
    for(int price = 100; price >= coin; --price) {
      for(int mult = 1; mult*coin <= price; ++mult) {
	if(overpay[price - coin*mult] + mult < overpay[price]) {
	  overpay[price] = overpay[price - coin*mult] + mult;
	}
      }
    }
  }

  int pay[201];
  int available[6];
  while(true) {
    int sum = 0;
    FORI(6) {
      cin >> available[i];
      sum += available[i];
    }
    if(sum == 0)
      return 0;
    double d; cin >> d;
    int toPay = (int)(100/5*(d+0.001));

    FORI(201)
      pay[i] = 9999;
    pay[0] = 0;

    for(int coinI = 5; coinI >= 0; --coinI) {
      int coin = coins[coinI];
      for(int price = 200; price >= coin; --price) {
	for(int mult = 1; mult <= available[coinI] && coin*mult <= price; ++mult) {
	  if(pay[price - coin*mult] + mult < pay[price]) {
	    pay[price] = pay[price - coin*mult] + mult;
	  }
	} // for mult
      } // for price
    } // for coinI

    int ret = 1000;
    for(int overpaid = 0; overpaid <= 100 && toPay + overpaid <= 200; ++overpaid) {
      int paid = toPay + overpaid;
      if(ret > pay[paid]+overpay[overpaid]) {
	ret = pay[paid]+overpay[overpaid];
      }
    }    
    printf("%3d\n", ret);
  } // while true
} // int main
