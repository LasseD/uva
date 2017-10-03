int main() {
  int cnt[10001];
  FORCAS {
    int price; cin >> price;
    memset(cnt, -1, sizeof(cnt));
    cnt[0] = 0;
    // Handle all coins:
    int coins; cin >> coins;
    FORI(coins) {
      int coin; cin >> coin;
      for(int p = 10000; p >= coin; --p) {
	if(cnt[p-coin] > -1 && (cnt[p] == -1 || cnt[p] > cnt[p-coin]+1))
	  cnt[p] = cnt[p-coin]+1;
      }
    }
    for(int ret = price; true; ++ret) {
      if(cnt[ret] > -1) {
	cout << ret << " " << cnt[ret] << endl;
	break;
      }	
    }
  }
  return 0;
}
