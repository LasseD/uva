typedef pair<PI,PI> Line;

bool rightTurnOrColinear(int diffX, int diffY, int x1, int y1, const PI &p) {
  return diffX*(p.YY-y1) <= diffY*(p.XX-x1);
}
bool rightTurnOrColinear(const PI &p1, const PI &p2, const PI &p) {
  return rightTurnOrColinear(p2.XX-p1.XX, p2.YY-p1.YY, p2.XX, p2.YY, p);
}
bool inside(PI a, PI b, PI c, PI p) {
  return ((rightTurnOrColinear(a, b, p) && rightTurnOrColinear(b, c, p) && rightTurnOrColinear(c, a, p)) || 
	  (rightTurnOrColinear(b, a, p) && rightTurnOrColinear(c, b, p) && rightTurnOrColinear(a, c, p)));
}

int main() {
  PI a[20];

  while(true) {
    GI(N); if(N == 0) return 0;
    FORI(N) {
      GS(s); if((int)(s[0]) != i+'A') die();
      cin >> a[i].XX >> a[i].YY;
    }
    
    // Try all:
    char best[3];
    int bestArea = -1;
    FORI(N) {
      for(int j = i+1; j < N; ++j) {
	for(int k = j+1; k < N; ++k) {
	  int x1 = a[i].XX, y1 = a[i].YY;
	  int x2 = a[j].XX, y2 = a[j].YY;
	  int x3 = a[k].XX, y3 = a[k].YY;

	  // Check area:
	  int area = ABS((y3-y1)*(x2-x1) - (y2-y1)*(x3-x1));
	  if(area < bestArea)
	    continue;
	  
	  // Check all outside:
	  bool ok = true;
	  for(int m = 0; m < N; ++m) {
	    if(m == i || m == j || m == k)
	      continue;
	    if(inside(a[i], a[j], a[k], a[m])) {
	      ok = false;
	      break;
	    }
	  } // FORM
	  if(ok) {
	    bestArea = area;
	    best[0] = (char)('A'+i);
	    best[1] = (char)('A'+j);
	    best[2] = (char)('A'+k);
	  }
	} // FORK
      } // FORJ
    } // FORI
    FORI(3)
      cout << best[i];
    cout << endl;
  } // while true
} // int main
