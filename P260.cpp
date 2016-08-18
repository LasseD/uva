#include <iostream>
#include <stdio.h>
#include <stack>

#define LINE_WIDTH 209
typedef std::pair<int,int> PP;
#define X first
#define Y second
typedef std::stack<PP> Stack;

bool makeLine(char *w, int n, int y) {
  if(w[y*LINE_WIDTH] != 'w')
    return false;
  Stack s;
  s.push(PP(0,y));
  while(!s.empty()) {
    PP p = s.top();
    s.pop();
    if(w[p.Y*LINE_WIDTH+p.X] != 'w')
      continue;
    if(p.X == n-1)
      return true;
    w[p.Y*LINE_WIDTH+p.X] = 'b';
    if(p.X > 0 && w[p.Y*LINE_WIDTH+p.X-1] == 'w')
      s.push(PP(p.X-1,p.Y));
    if(p.X < n-1 && w[p.Y*LINE_WIDTH+p.X+1] == 'w')
      s.push(PP(p.X+1,p.Y));
    if(p.Y < n-1 && w[(p.Y+1)*LINE_WIDTH+p.X] == 'w')
      s.push(PP(p.X,p.Y+1));
    if(p.Y > 0 && w[(p.Y-1)*LINE_WIDTH+p.X] == 'w')
      s.push(PP(p.X,p.Y-1));
    if(p.Y < n-1 && p.X < n-1 && w[(p.Y+1)*LINE_WIDTH+p.X+1] == 'w')
      s.push(PP(p.X+1,p.Y+1));
    if(p.Y > 0 && p.X > 0 && w[(p.Y-1)*LINE_WIDTH+p.X-1] == 'w')
      s.push(PP(p.X-1,p.Y-1));
  }
  return false;
}

int main() {
  char c, w[LINE_WIDTH*LINE_WIDTH];
  for(int cas = 1; true; ++cas) {
    gets(w);
    int n = 0;
    for(int i = 0; isdigit(c = w[i]); ++i)
      n = 10*n + (w[i]-'0');
    if(n == 0)
      return 0;
    for(int i = 0; i < n; ++i)
      gets(&w[i*LINE_WIDTH]);
    bool whiteWins = false;
    for(int y = 0; y < n; ++y) {
      if(makeLine(w, n, y)) {
	whiteWins = true;
	break;
      }
    }
    if(whiteWins)
      std::cout << cas << " W" << std::endl;
    else
      std::cout << cas << " B" << std::endl;
  }
}
