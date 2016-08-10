#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstring>

typedef std::pair<int,int> Pos;
#define X first
#define Y second

bool readInts(char *w, int &a, int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
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
  return aDone;
}

void readInt(char *w, int &a) {
  a = 0;
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      a = a*10 + (w[i]-'0');
    }
    else {
      if(!isprint(w[i]))
	break;
    }
  }
}

void computeCC(int *sizes, int W, int H, Pos init) {
  // 1: compute size:
  int size = 0;
  std::stack<Pos> s;
  s.push(init);
  while(!s.empty()) {
    Pos p = s.top();
    s.pop();
    int idx = 100*p.Y+p.X;
    if(sizes[idx] != -2)
      continue;
    ++size;
    sizes[idx] = -1;
    for(int dx = -1; dx <= 1; dx+=1) {
      int xx = p.X+dx;
      if(xx < 0 || xx >= W)
	continue;
      for(int dy = -1; dy <= 1; dy+=1) {
	int yy = dy+p.Y;
	if(yy < 0 || yy >= H)
	  continue;
	idx = 100*yy+xx;
	if(sizes[idx] == -2)
	  s.push(Pos(xx,yy));
      } // dy
    } // dx
  } // while !s.empty()

  //std::cerr << "Found patch of size " << size << " at " << init.X << "," << init.Y << std::endl;

  // 2: distribute result:
  s.push(init);
  while(!s.empty()) {
    Pos p = s.top();
    s.pop();
    int idx = 100*p.Y+p.X;
    if(sizes[idx] != -1)
      continue;
    sizes[idx] = size;
    for(int dx = -1; dx <= 1; dx+=1) {
      int xx = p.X+dx;
      if(xx < 0 || xx >= W)
	continue;
      for(int dy = -1; dy <= 1; dy+=1) {
	int yy = dy+p.Y;
	if(yy < 0 || yy >= H)
	  continue;
	idx = 100*yy+xx;
	if(sizes[idx] == -1)
	  s.push(Pos(xx,yy));
      } // dy
    } // dx
  } // while !s.empty()
}

int main() {
  char w[309];
  int N, x, y, sizes[10000];
  gets(w);
  readInt(w, N);
  gets(w);

  for(int cas = 0; cas < N; ++cas) {
    if(cas > 0)
      std::cout << std::endl;
    int H = 0;
    int W = 0;
    // read data:
    while(true) { // get rows
      gets(w);
      if(w[0] != 'W' && w[0] != 'L')
	break;
      while(w[W] == 'W' || w[W] == 'L')
	++W;
      for(x = 0; x < W; ++x)
	sizes[H*100+x] = w[x] == 'W' ? -2 : -99;
      ++H;
    }

    // Compute width:
    //std::cerr << "W=" << W << ", H=" << H << std::endl;

    for(x = 0; x < W; ++x) {
      for(y = 0; y < H; ++y) {
	if(sizes[y*100+x] != -2)
	  continue;
	// Compute connected component starting at x, y:
	computeCC(sizes, W, H, Pos(x,y));	
      }
    }
    while(readInts(w, y, x)) {
      --x;--y;
      //std::cerr << "Size of wetland at location " << x << ", " << y << std::endl;
      std::cout << sizes[y*100+x] << std::endl;
      if(!gets(w))
	return 0;
    }
  }
}
