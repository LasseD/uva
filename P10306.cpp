int main() {
  int M[301][301];
  FORCAS {
    GI(m); GI(S); // m = num coins, S = e-modulus.
    // Reset M:
    FORX(S+1) {
      FORY(S+1)
	M[x][y] = -1;
    }
    M[0][0] = 0;

    // Handle coins:
    int ret = 9999999;
    FORI(m) {
      GI(a); GI(b);
      for(int x = a; x <= S; ++x) {
	for(int y = b; y <= S; ++y) {
	  if(M[x-a][y-b] == -1)
	    continue;
	  if(M[x][y] == -1 || M[x][y] > M[x-a][y-b]+1)
	    M[x][y] = M[x-a][y-b]+1;
	  if(x*x+y*y == S*S && ret > M[x][y])
	    ret = M[x][y];
	}
      }
    }
    if(ret == 9999999)
      cout << "not possible" << endl;
    else
      cout << ret << endl;
      
  }
  return 0;
}
