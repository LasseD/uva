int main() {
  int budget, n, favour[10201], p, f;
  while(cin >> budget >> n) {
    memset(favour, 0, sizeof(favour));
    
    FORI(n) {
      cin >> p >> f;
      for(int price = budget + 200; price >= p; --price) {
	if(favour[price-p] == 0 && price-p != 0)
	  continue;
	if(f+favour[price-p] > favour[price])
	  favour[price] = f+favour[price-p];
      }
    }
    int bestFavour = 0;
    //cerr << "Computing for budget=" << budget << ", n=" << n << endl;
    for(int ret = budget + 200; ret >= 0; --ret) {
      if(ret > budget && ret <= 2000)
	continue;
      if(favour[ret] > bestFavour) {
	//cerr << "Best " << favour[ret] << " @ " << ret << endl;
	bestFavour = favour[ret];
      }
      else if(favour[ret] > 0) {
	//cerr << "Ignore " << favour[ret] << " @ " << ret << endl;
      }
    }
    cout << bestFavour << endl;
  }
  return 0;
}
