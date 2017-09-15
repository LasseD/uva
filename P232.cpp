int main() {
  string M[12];
  int a[10][10];
  int r, c;
  for(int cas = 1; true; ++cas) {
    cin >> r;
    if(r==0)
      return 0;
    if(cas != 1)
      printf("\n");
	      
    cin >> c;
    FORI(r)
      cin >> M[i];

    // Build a in order to get indices :)
    int cnt = 1;
    FORY(r) {
      FORX(c) {
	if(M[y][x] != '*' && (x == 0 || y == 0 || M[y-1][x] == '*' || M[y][x-1] == '*'))
	  a[y][x] = cnt++;
	else
	  a[y][x] = -1;
      }
    }

    printf("puzzle #%d:\n", cas);
    printf("Across\n");
    FORY(r) {
      FORX(c) {
	if(M[y][x] != '*' && (x == 0 || M[y][x-1] == '*')) {
	  printf("%3d.", a[y][x]);
	  // Print all letters:
	  for(int xx = x; xx < c && M[y][xx] != '*'; ++xx)
	    printf("%c", M[y][xx]);
	  printf("\n");
	}
      }
    }
    printf("Down\n");
    FORY(r) {
      FORX(c) {
	if(M[y][x] != '*' && (y == 0 || M[y-1][x] == '*')) {
	  printf("%3d.", a[y][x]);
	  // Print all letters:
	  for(int yy = y; yy < r && M[yy][x] != '*'; ++yy)
	    printf("%c", M[yy][x]);
	  printf("\n");
	}
      }
    }
    
    
  }
}
