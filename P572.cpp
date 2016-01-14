#include <iostream>
#include <stdio.h>
#include <stack>

typedef std::pair<int,int> Pos;
#define X first
#define Y second

void readInts(int &a, int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      if(aDone)
	b = b*10 + (w[i]-'0');
      else {
	a = a*10 + (w[i]-'0');
	aStarted = true;
      }
    }
    else {
      if(!isprint(w[i]))
	break;
      if(aStarted)
	aDone = true;
    }
  }
}

int main() {
  int m, n, a[10000]; // 0=no oil, 1=uncounted oil, 2=counted oil.
  char w[109];
  while(true) {    
    // read data:
    readInts(m, n);
    if(m == 0 && n == 0) // m = rows, n = columns.
      return 0;
    for(int y = 0; y < m; ++y) { // get rows
      gets(w);
      for(int x = 0; x < n; ++x)
	a[n*y+x] = (w[x] == '*' ? 0 : 1);
    }
    // propagate fields:
    int cnt = 0;
    std::stack<Pos> s;
    for(int y = 0; y < m; ++y) {
      for(int x = 0; x < n; ++x) {
	int idx = n*y+x;
	if(a[idx] != 1)
	  continue;
	++cnt;
	// propagate:
	s.push(Pos(x,y));
	while(!s.empty()) {
	  Pos p = s.top();
	  s.pop();
	  idx = n*p.Y+p.X;
	  if(a[idx] != 1)
	    continue;
	  a[idx] = 2;
	  for(int dx = -1; dx <= 1; ++dx) {
	    int xx = p.X+dx;
	    if(xx < 0 || xx >= n)
	      continue;
	    for(int dy = -1; dy <= 1; ++dy) {
	      int yy = dy+p.Y;
	      if(yy < 0 || yy >= m)
		continue;
	      if(a[n*yy+xx] == 1)
		s.push(Pos(xx,yy));
	    } // dy
	  } // dx
	} // while !s.empty()
      } // x
    } // y
    std::cout << cnt << std::endl;
  } // while(true)
} // int main
