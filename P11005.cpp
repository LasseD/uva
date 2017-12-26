int prices[36];

LL getPrice(int N, int base) {
  LL ret = 0;
  if(N == 0)
    return prices[0];
  while(N > 0) {
    ret += prices[N % base];
    N/=base;
  }
  return ret;
}

int main() {
  LL priceForBase[37];

  FORCAS {
    if(cas != 0)
      cout << endl;
    cout << "Case " << cas+1 << ":" << endl;

    FORI(36)
      cin >> prices[i];
    GI(Q);
    FORI(Q) {
      GI(N);
      cout << "Cheapest base(s) for number " << N << ":";
      LL minPrice = priceForBase[2] = getPrice(N, 2);
      for(int base = 3; base <= 36; ++base) {
	priceForBase[base] = getPrice(N, base);
	minPrice = MIN(minPrice, priceForBase[base]);
      }
      for(int base = 2; base <= 36; ++base) {
	if(minPrice == priceForBase[base])
	  cout << " " << base;
      }
      cout << endl;
    }
  }
}
