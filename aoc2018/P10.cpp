#define SIZE 1000

// Remove "position=<", "> velocity=<", ",", and ">" from input.
int main() {
  vector<PI> p, v;
  int a, b, c, d;
  while(cin >> a >> b >> c >> d) {
    p.push_back(PI(a,b));
    v.push_back(PI(c,d));
    //cout << "(" << a << "," << b << ") -> )" << c << "," << d << ")" << endl;
  }
  int lastW = 9999999, lastH = 9999999;

  bool Q[SIZE][SIZE];
  
  FORK(100000) {    
    FORY(SIZE) {
      FORX(SIZE) {
	Q[y][x] = false;
      }
    }
    int miX = 9999999, miY = 9999999, maX = -9999999, maY = -9999999;    
    FORI((int)p.size()) {
      int x = p[i].XX + k*v[i].XX;
      int y = p[i].YY + k*v[i].YY;
      miX = min(miX, x);
      maX = max(maX, x);
      miY = min(miY, y);
      maY = max(maY, y);
    }
    int w = maX-miX+1;
    int h = maY-miY+1;
    cout << "Size: " << w << " x " << h << endl;
    if(w > lastW && h >lastH) {
      return 0; // Done.
    }
    lastW = w;
    lastH = h;
    bool ok = true;
    FORI((int)p.size()) {
      int x = p[i].XX + k*v[i].XX - miX;
      int y = p[i].YY + k*v[i].YY - miY;
      if(x < SIZE && y < SIZE)
	Q[y][x] = true;
      else {
	ok = false;
	break;
      }
    }
    if(ok) {
      cout << "Time " << k << endl;
      FORY(maY-miY+1) {
	FORX(maX-miX+1) {
	  if(Q[y][x])
	    cout << "#";
	  else
	    cout << ".";
	}
	cout << endl;
      }
    }
  }
}
