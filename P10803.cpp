double dist(PI a, PI b) {
  double dx = a.XX-b.XX;
  double dy = a.YY-b.YY;
  return sqrt(dx*dx+dy*dy);
}

int main() {
  double a[101][101];
  PI positions[101];
  FORCAS {
    int N; cin >> N;
    FORI(N) {
      FORJ(N) {
	a[i][j] = 1e9;
      }
    }

    FORI(N) {
      cin >> positions[i].XX >> positions[i].YY;
      a[i][i] = 0;
      FORJ(i) {
	double d = dist(positions[i], positions[j]);
	if(d <= 10.0)
	  a[j][i] = a[i][j] = d;
      }
    }
    
    bool improved = true;
    double max;
    while(improved) {
      improved = false;
      max = 0;
      FORI(N) {
	FORJ(i) {
	  FORK(N) {
	    if(k == i || k == j)
	      continue;
	    if(a[i][j] > a[i][k] + a[k][j]) {
	      improved = true;
	      a[i][j] = a[j][i] = a[i][k] + a[k][j];
	    }
	  } // k
	  max = MAX(max, a[i][j]);
	  //cerr << " " << a[i][j];
	} // j
	//cerr << endl;
      } // i
    } // improved

    if(max < 1e8)
      printf("Case #%d:\n%.4lf\n\n", cas+1, max);
    else
      printf("Case #%d:\nSend Kurdy\n\n", cas+1);
  }
  return 0;
}
