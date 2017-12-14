#define XXX 99999999

int main() {
  long wind[10][1009];
  long a[10][1009];
  // Climb: 60 fuel, hold 30, sink 20.
  // 9 miles max.
  FORCAS {
    GI(X); X/=100;
    
    FORY(10) {
      FORX(X) {
	cin >> wind[9-y][x];	
      }
    }

    //init:
    a[0][0] = 0;
    for(int y = 1; y < 10; ++y)
      a[y][0] = XXX; // can't be here.

    // Do computation:
    for(int x = 1; x < X; ++x) {
      FORY(10) {
	long best = XXX;
	if(a[y][x-1] != XXX)
	  best = -wind[y][x-1] + 30 + a[y][x-1]; // hold
	if(y > 0 && a[y-1][x-1] != XXX) // climb:
	  best = MIN(best, -wind[y-1][x-1] + 60 + a[y-1][x-1]);
	if(y < 9 && a[y+1][x-1] != XXX) // sink:
	  best = MIN(best, -wind[y+1][x-1] + 20 + a[y+1][x-1]);

	a[y][x] = best; // subtract wind speed.
      }
      //if(x != X-1)
	a[0][x] = XXX; // Can't skim the bottom.
    }

    /*
    FORY(10) {
      FORX(X) {
	if(a[9-y][x] > 999999)
	  cerr << " ---";
	else
	  cerr << " " << a[9-y][x];	
      }
      cerr << endl;
    }*/

    cout << MIN(a[0][X-1]+30-wind[0][X-1], a[1][X-1]+20-wind[1][X-1]) << endl << endl;
  }
  return 0;
}
