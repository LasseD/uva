#include <stdio.h>
#include <iostream>
#include <stack>
#include <sstream>

typedef std::string String;
typedef std::pair<int,int> Point;

#define X first
#define Y second

void stepCC(int x, int y, int n, int *m, std::stack<Point> &s, int color) {
  if(x < 0 || x >= n || y < 0 || y >= n)
    return;
  if(m[n*x+y] != color)
    return;
  s.push(Point(x, y));
}

// size connected component.
int connectedComponent(int x, int y, int *m, int n) {
  std::stack<Point> s;
  int size = 0;
  int color = m[n*x + y];
  s.push(Point(x,y));
  while(!s.empty()) {
    Point p = s.top();
    s.pop();
    if(m[n*p.X + p.Y] < 0)
      continue; // Already handled.
    ++size;
    
    stepCC(p.X-1, p.Y, n, m, s, color);
    stepCC(p.X+1, p.Y, n, m, s, color);
    stepCC(p.X, p.Y-1, n, m, s, color);
    stepCC(p.X, p.Y+1, n, m, s, color);
    m[n*p.X + p.Y] = -1;
  }
  //std::cerr << "Size of component " << color << ": " << size << " vs n=" << n << std::endl;
  return size;
}

int main() {
  int n, m[99*99];

  while(true) {
    String w;
    std::getline(std::cin,w);
    std::stringstream ssM; ssM << w; ssM >> n;

    if(n == 0)
      return 0;
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < n; ++j)
	m[i*n+j] = n;

    bool ok = true;
    for(int i = 0; i < n-1; ++i) {
      std::getline(std::cin,w);
      std::stringstream ssL; ssL << w;
      int x, y, j = 0;
      while(ssL >> x >> y) {
	--x;
	--y;
	m[x*n+y] = i+1;
	++j;
      }
      ok = ok && (j >= n);      
    }
    //std::cerr << "Line ok: " << ok << std::endl;

    for(int x = 0; ok && x < n; ++x) {
      for(int y = 0; ok && y < n; ++y) {
	if(m[n*x+y] < 0)
	  continue; // already handled.
	int size = connectedComponent(x, y, m, n);
	if(size != n)
	  ok = false;
      }
    }

    if(ok)
      std::cout << "good" << std::endl;
    else
      std::cout << "wrong" << std::endl;
  }
}

