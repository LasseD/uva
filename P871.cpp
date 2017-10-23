string M[26];
int N;

int get(int x, int y) {
  if(M[x][y] == '0')
    return 0;
  int ret = 1;
  M[x][y] = '0';
  for(int xx = x-1; xx <= x+1; ++xx) {
    if(xx < 0 || xx >= N)
      continue;
    for(int yy = y-1; yy <= y+1; ++yy) {
      if(yy < 0 || yy >= N)
	continue;
      ret += get(xx, yy);
    }
  }
  return ret;
}

int main() {
  FORCAS {
    if(cas > 0)
      cout << endl;
    cin >> M[0];
    N = (int)M[0].size();
    FORI(N-1)
      cin >> M[i+1];

    int max = 0;
    FORX(N) {
      FORY(N) {
	int size = get(x, y);
	if(size > max)
	  max = size;	  
      }
    }
    cout << max << endl;
  }
  return 0;
}
