/*
Process lines while maintaining length of up-rays:

Example:
Maze   Up-rays Max areas
XX-XX  00100   00100
XX--X  00210   00220
----X  11320   12340
XX-XX  00400   00400

=> O(n^3)
 */
int main () {
  int upRays[100];
  bool board[10000];
  FORCAS {
    int s, n, r1, c1, r2, c2;
    cin >> s >> n; // board size s, blocks n

    memset(upRays, 0, s*sizeof(int));
    memset(board, false, s*s*sizeof(bool));
    // Read blocks:
    FORI(n) {
      cin >> r1 >> c1 >> r2 >> c2;
      --r1; --r2; --c1; --c2;
      for(int x = c1; x <= c2; ++x) {
	for(int y = r1; y <= r2; ++y) {
	  board[y*s+x] = true;
	}
      }
    }

    // Compute area:
    int area = 0;
    for(int y = 0; y < s; ++y) {
      // update uprays:
      for(int x = 0; x < s; ++x) {
	if(!board[y*s+x])
	  ++upRays[x];
	else
	  upRays[x] = 0;
      }
      //cerr << "N=" << N << ", W=" << w << endl;
      for(int x = 0; x < s; ++x) {
	int upRay = upRays[x];
	if(upRay > 0) {
	  int xMin = x, xMax = x;
	  while(xMin > 0 && upRays[xMin-1]>=upRay)
	    --xMin;
	  while(xMax < s-1 && upRays[xMax+1]>=upRay)
	    ++xMax;
	  int newArea = upRay*(xMax-xMin+1);
	  if(area < newArea)
	    area = newArea;
	}
      }
    } // for y
    cout << area << endl;
  } // FORCAS
  return 0;
}
