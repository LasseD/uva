#include <iostream>
#include <stdio.h>
#include <stack>

typedef std::pair<int,int> Pos;
#define X first
#define Y second

bool readInt(int &a) {
  a = 0;
  char w[20];
  if(!gets(w))
    return false;
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      a = a*10 + (w[i]-'0');
    }
    else {
      if(!isprint(w[i]))
	break;
    }
  }
  return true;
}

int main() {
  int m, a[900]; // 0=no oil, 1=uncounted oil, 2=counted oil.
  char w[30];
  for(int cas = 1; readInt(m); ++cas) {    
    for(int y = 0; y < m; ++y) { // get rows
      gets(w);
      for(int x = 0; x < m; ++x)
	a[m*y+x] = (w[x] == '0' ? 0 : 1);
    }
    // propagate fields:
    int cnt = 0;
    std::stack<Pos> s;
    for(int y = 0; y < m; ++y) {
      for(int x = 0; x < m; ++x) {
	int idx = m*y+x;
	if(a[idx] != 1)
	  continue;
	++cnt;
	// propagate:
	s.push(Pos(x,y));
	while(!s.empty()) {
	  Pos p = s.top();
	  s.pop();
	  idx = m*p.Y+p.X;
	  if(a[idx] != 1)
	    continue;
	  a[idx] = 2;
	  for(int dx = -1; dx <= 1; ++dx) {
	    int xx = p.X+dx;
	    if(xx < 0 || xx >= m)
	      continue;
	    for(int dy = -1; dy <= 1; ++dy) {
	      int yy = dy+p.Y;
	      if(yy < 0 || yy >= m)
		continue;
	      if(a[m*yy+xx] == 1)
		s.push(Pos(xx,yy));
	    } // dy
	  } // dx
	} // while !s.empty()
      } // x
    } // y
    std::cout << "Image number " << cas << " contains " << cnt << " war eagles."<< std::endl;
  } // while(true)
  return 0;
} // int main
