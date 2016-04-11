#include <iostream>
#include <stdio.h>
#include <stack>
#include <vector>
#include <algorithm>

typedef std::pair<int,int> Pos;
typedef std::pair<int,char> Info;
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
void readInt(int &a) {
  a = 0;
  char w[20];
  gets(w);
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

int main() {
  int N, H, W;
  readInt(N);

  for(int cas = 1; cas <= N; ++cas) {
    // read data:
    readInts(H, W);
    char *a = new char[W*H];
    char *w = new char[W+9];
    for(int y = 0; y < H; ++y) { // get rows
      gets(w);
      for(int x = 0; x < W; ++x)
	a[W*y+x] = w[x];
    }
    delete[] w;

    int regions[26]; // letter 'a'+i -> count.
    for(int i = 0; i < 26; ++i) {
      regions[i] = 0;
    }
    //  Info infos[26];
    
    // propagate fields:
    std::stack<Pos> s;
    for(int y = 0; y < H; ++y) {
      for(int x = 0; x < W; ++x) {
	int idx = W*y+x;
	if(a[idx] == '\0')
	  continue;
	char currentRegion = a[idx];
	++regions[currentRegion-'a'];

	// propagate:
	s.push(Pos(x,y));
	while(!s.empty()) {
	  Pos p = s.top();
	  s.pop();
	  idx = W*p.Y+p.X;
	  if(a[idx] == '\0')
	    continue;
	  a[idx] = '\0';
	  for(int dx = -1; dx <= 1; dx+=2) {
	    int xx = p.X+dx;
	    if(xx < 0 || xx >= W)
	      continue;
	    if(a[W*p.Y+xx] == currentRegion)
	      s.push(Pos(xx,p.Y));
	  }
	  for(int dy = -1; dy <= 1; dy+=2) {
	    int yy = dy+p.Y;
	    if(yy < 0 || yy >= H)
	      continue;
	    if(a[W*yy+p.X] == currentRegion)
	      s.push(Pos(p.X,yy));
	  }
	} // while !s.empty()
      } // x
    } // y
    delete[] a;

    // Output:
    std::vector<Info> v;
    for(int i = 0; i < 26; ++i) {
      if(regions[i] == 0)
	continue;
      v.push_back(Info(-regions[i], (char)('a'+i)));
    }
    std::sort(v.begin(), v.end());    
    std::cout << "World #" << cas << std::endl;
    for(std::vector<Info>::const_iterator it = v.begin(); it != v.end(); ++it)
      std::cout << it->second << ": " << (-it->first) << std::endl;
  } // while(true)
} // int main
