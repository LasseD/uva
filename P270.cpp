typedef PI Fraq;
#define Nom first
#define Denom second

int gcd(int a, int b) {
  int c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

Fraq reduce(int nom, int denom) {
  if(denom < 0) {
    denom = -denom;
    nom = -nom;
  }
  int g = gcd(ABS(nom), denom);
  return Fraq(nom/g, denom/g);
}

int main() {
  string line;
  getline(cin, line);
  int cases;
  stringstream ss1; ss1 << line; ss1 >> cases;
  getline(cin, line);
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;
    // Read points:
    vector<Point> pts;
    PI pt;
    while(true) {
      getline(cin, line);
      stringstream ss2; ss2 << line;
      if(!(ss2 >> pt.XX >> pt.YY))
	break;
      pts.push_back(pt);
    }
    sort(pts.begin(), pts.end()); // Sort by x, then y.
    int N = (int)pts.size();
    // Try where all points are left-most and see how many that lie on various angles:
    //cerr << "Handling " << N << " points." << endl;
    int best = 0;
    for(int a = 0; a < N; ++a) {
      PI pa = pts[a];
      map<Fraq,int> lines; // line -> count.
      int curBest = 0;
      for(int b = a+1; b < N; ++b) {
	PI pb = pts[b];
	Fraq slope = reduce(pa.XX - pb.XX, pa.YY - pb.YY);
	++lines[slope];
	if(lines[slope] > curBest)
	  ++curBest; 
      }
      ++curBest; // Count the point itself.
      if(curBest > best)
	best = curBest;
    }
    cout << best << endl;
  }
  return 0;
}
