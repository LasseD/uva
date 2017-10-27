int gcd(int a, int b) {
  int c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

typedef map<double,PI> MAP;

bool leftTurn(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.XX-lineStart.XX)*(p.YY-lineStart.YY) - (lineEnd.YY-lineStart.YY)*(p.XX-lineStart.XX) > 0;
}
bool colinear(const Point &lineStart, const Point &lineEnd, const Point &p) {
  return (lineEnd.XX-lineStart.XX)*(p.YY-lineStart.YY) - (lineEnd.YY-lineStart.YY)*(p.XX-lineStart.XX) == 0;
}

bool ok(PI p, int N, PI *pts) {
  int left = 0, right = 0;
  PI p0(0,0);
  FORI(N) {
    PI q = pts[i];
    if(colinear(p0, p, q))
      return false;
    if(leftTurn(p0, p, q))
      ++left;
    else
      ++right;
  }
  return left + right == N && left == right;
}

int main() {
  // Precompute rotation map:
  MAP M; // Angle -> (A,B) = (x,y) in line (0,0) -> (x,y)
  M[M_PI/2] = PI(0,1);
  M[0] = PI(1,0);
  for(int x = 1; x <= 500; ++x) {
    for(int y = -500; y <= 500; ++y) {
      if(y == 0)
	continue;
      int g = gcd(ABS(x), ABS(y));
      if(g != 1)
	continue; // already added.
      M[atan2(y,x)] = PI(x,y);
      //cerr << x << "," << y << " => " << atan2(y,x) << endl;
    }
  }

  PI pts[100];
  while(true) {
    GI(N); if(N == 0) return 0;
    N*=2;
    FORI(N) {
      cin >> pts[i].XX >> pts[i].YY;
    }
    bool any = false;
    FORI(N) {
      PI p = pts[i], pLow, pHigh;
      double a = atan2(p.YY,p.XX);      
      MAP::const_iterator itLow = M.find(a);
      if(itLow == M.begin())
	pLow = M.rbegin()->second;
      else {
	--itLow;
	pLow = itLow->second;
      }
      if(ok(pLow, N, pts)) {
	cout << pLow.YY << " " << -pLow.XX << endl;
	any = true;
	break;
      }
		
      MAP::const_iterator itHigh = M.find(a);
      ++itHigh;
      if(itHigh == M.end())
	pHigh = M.begin()->second;
      else
	pHigh = itHigh->second;
      if(ok(pHigh, N, pts)) {
	cout << pHigh.YY << " " << -pHigh.XX << endl;
	any = true;
	break;
      }
    }
    if(!any)
      dieSlowly();
    
  } // while(true)
} // int main
