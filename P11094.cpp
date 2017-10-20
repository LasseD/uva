// Coordinates (x,y) ~ (M,N)

int handle(int x, int y, bool map[][22], int M, int N) {
  if(!map[x][y])
    return 0;
  int ret = 1;
  map[x][y] = false;
  if(x > 0)
    ret += handle(x-1, y, map, M, N);
  if(x < M-1)
    ret += handle(x+1, y, map, M, N);
  ret += handle(x, (y+1)%N, map, M, N);
  ret += handle(x, (y+N-1)%N, map, M, N);
  return ret;
}

int main() {
  int M, N;
  bool map[22][22]; // true => land.
  string line;
  while(true) {
    getline(cin, line);
    stringstream ss1; ss1 << line; if(!(ss1 >> M >> N)) return 0;
    char firstChar;
    FORX(M) {
      getline(cin, line);
      if((int)line.size() != N)
	die();
      if(x == 0)
	firstChar = line[0];
      FORY(N) {
	map[x][y] = line[y] == firstChar;
      }
    }
    getline(cin, line);
    int kx, ky;
    stringstream ss2; ss2 << line; ss2 >> kx >> ky;
    if(!map[kx][ky]) {
      // FLIP ALL!
      FORY(N) {
	FORX(M) {
	  map[x][y] = !map[x][y];
	}
      }
    }
    
    handle(kx, ky, map, M, N);
    int max = 0;
    FORY(N) {
      FORX(M) {
	int continentSize = handle(x,y, map, M, N);
	//cerr << "Continent at " << x << "," << y << ": " << continentSize << endl;
	max = MAX(max,continentSize);
      }
    }
    cout << max << endl;
    getline(cin, line);
  }
  return 0;
}
