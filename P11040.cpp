int main() {
  ULL a[9][9];
  FORCAS {
    for(int y = 0; y < 9; y+=2) {
      for(int x = 0; x <= y; x+=2) {
	cin >> a[y][x];
      }
    }
    // Fill last row:    
    for(int x = 1, idx = 0; x < 9; x += 2, idx+=2) {
      a[8][x] = (a[6][idx]-a[8][x-1]-a[8][x+1])/2;
      //cerr << "Set lowest x=" << x << ": " << a[8][x] << endl;
    }
    // Fill remainder:
    for(int y = 7; y > 0; --y) {
      for(int x = 0; x <= y; ++x) {
	a[y][x] = a[y+1][x]+a[y+1][x+1];
      }
    }
    // Output:
    FORY(9) {
      cout << a[y][0];
      FORX(y) {
	cout << " " << a[y][x+1];
      }
      cout << endl;
    }
  }
  return 0;
}
