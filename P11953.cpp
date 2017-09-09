void clearShip(string *M, int N, int x, int y) {
  if(M[y][x] == '.')
    return;
  M[y][x] = '.';
  if(x > 0)
    clearShip(M, N, x-1, y);
  if(y > 0)
    clearShip(M, N, x, y-1);
  if(x < N-1)
    clearShip(M, N, x+1, y);
  if(y < N-1)
    clearShip(M, N, x, y+1);  
}

int main() {
  int cases, N;
  string M[100];
  scanf("%d", &cases);
  for(int cas = 0; cas < cases; ++cas) {
    scanf("%d", &N);
    getchar();
    FORI(N) {
      getline(cin, M[i]);
    }

    int ret = 0;
    FORY(N) {
      FORX(N) {
	if(M[y][x] == 'x') {
	  clearShip(M, N, x, y);
	  ++ret;
	}
      }
    }
    cout << "Case " << cas+1 << ": " << ret << endl;
  }
}
