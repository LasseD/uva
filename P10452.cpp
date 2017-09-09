int main() {
  int PATH[7] = {'I','E','H','O','V','A','#'};

  string M[10];
  int w, h, x, y;
  
  FORCAS {
    cin >> h >> w;
    FORI(h)
      cin >> M[i];
    y = h-1;
    FORI(w) {
      if(M[y][i] == '@')
	x = i;
    }
    FORI(7) {
      if(i > 0)
	cout << " ";
      if(x > 0 && M[y][x-1] == PATH[i]) {
	cout << "left";
	--x;
      }
      else if(x < w-1 && M[y][x+1] == PATH[i]) {
	cout << "right";
	++x;
      }
      else {
	cout << "forth";
	--y;
      }
    }
    cout << endl;
  }
}
