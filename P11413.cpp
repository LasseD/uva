bool ok(int cap, int n, int m, int *c) {
  int curContainer = 0;
  int curLevel = 0;
  FORI(n) {
    if(curLevel + c[i] > cap) {
      ++curContainer;
      curLevel = c[i];
      if(curContainer >= m) {
	//cerr << "cap " << cap << " not ok" << endl;
	return false;
      }
    }
    else
      curLevel += c[i];
  }
  //cerr << "cap " << cap << " ok, m=" << m << ", n=" << n << endl;
  return true;
}

int main() {
  int n, m, c[1000];
  while(cin >> n >> m) {
    int maxVessel = 0;
    int sumVessels = 0;
    FORI(n) {
      cin >> c[i];
      sumVessels+=c[i];
      if(c[i] > maxVessel)
	maxVessel = c[i];
    }
    int low = maxVessel-1; // Too little
    int high = sumVessels; // Enough
    while(low < high-1) {
      int mid = (low+high)/2;
      if(ok(mid, n, m, c))
	high = mid;
      else
	low = mid;
    }
    cout << high << endl;
  }
  return 0;
}
