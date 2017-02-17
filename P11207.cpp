int main() {
  int N; 
  double w, h;
  while(true) {
    cin >> N;
    if(N == 0)
      return 0;
    int bestI = -1;
    double bestSize = 0;
    FORI(N) {
      cin >> w >> h;
      if(w < h) // w >= h
	swap(w,h);
      double size4 = MIN(h, w/4.0);
      double size2 = MIN(w/2.0, h/2.0);
      double size = MAX(size2, size4);
      if(size > bestSize) {
	bestSize = size;
	bestI = i;
      }
    }
    cout << bestI+1 << endl;
  }
}
