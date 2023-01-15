int main() {
  string s;
  int x = 0, y = 0, dir = 1; // 0 North, 1 East, 2 South, 3 West.
  int vx = 10, vy = -1;
  while(cin >> s) {
    char c = s[0];
    int v = 0;
    for(int i = 1; i < (int)s.size(); i++) {
      v = 10*v + s[i]-'0';
    }
    // Simulate:
    switch(c) {
    case 'N':
      vy-=v;
      break;
    case 'S':
      vy+=v;
      break;
    case 'E':
      vx+=v;
      break;
    case 'W':
      vx-=v;
      break;
    case 'L':
      for(int i = 0; i < v; i+=90) {
	swap(vx,vy);
	vy = -vy;
      }
      break;
    case 'R':
      for(int i = 0; i < v; i+=90) {	
	swap(vx,vy);
	vx = -vx;
      }
      break;
    case 'F':
      x += v * vx;
      y += v * vy;
      break;
    }
    cout << "Moved " << c << " " << v << " to " << x << ", " << y << ", waypoint " << vx << ", "<< vy <<endl;
  } // while cin
  cout << (abs(x)+abs(y)) << endl;
}

/* Part 1 simulation:
switch(c) {
    case 'N':
      y-=v;
      break;
    case 'S':
      y+=v;
      break;
    case 'E':
      x+=v;
      break;
    case 'W':
      x-=v;
      break;
    case 'L':
      for(int i = 0; i < v; i+=90)
	dir = (dir+3)%4;
      break;
    case 'R':
      for(int i = 0; i < v; i+=90)
	dir = (dir+1)%4;
      break;
    case 'F':
      switch(dir) {
      case 0://'N':
	y-=v;
	break;
      case 2:
	y+=v;
	break;
      case 1:
	x+=v;
	break;
      case 3:
	x-=v;
	break;
      }
      break;
      }*/
