#include <iostream>
#include <stdio.h>
#include <stack>

typedef std::pair<int,int> Point;
#define X first
#define Y second
#define WIDTH 83
typedef std::stack<Point> Stack;

void die() {
  int *a = NULL;
  a[5] = 6;
}

int main() {
  char c, w[WIDTH*32];
  int cases = 0;
  gets(w);
  for(int i = 0; isdigit(c = w[i]); ++i)
    cases = 10*cases + (c-'0');

  for(int cas = 0; cas < cases; ++cas) {
    int lines = 0;
    bool foundStart = false;
    Point start;
    
    do {
      gets(&w[WIDTH*lines]);
      if(!foundStart) {
	for(int i = 1; isprint(c = w[WIDTH*lines+i]); ++i) {
	  if(c == '*') {
	    start = Point(i, lines);
	    foundStart = true;
	    w[WIDTH*lines+i] = ' ';
	    break;
	  }
	}
      }
      ++lines;
    } 
    while(w[WIDTH*(lines-1)] != '_');

    if(!foundStart)
      die();

    Stack s;
    s.push(start);
    
    while(!s.empty()) {
      Point p = s.top(); s.pop();
      if(w[WIDTH*p.Y+p.X] != ' ')
	continue;
      w[WIDTH*p.Y+p.X] = '#';
      if(w[WIDTH*p.Y+p.X-1] == ' ')
	s.push(Point(p.X-1, p.Y));
      if(w[WIDTH*(p.Y-1)+p.X] == ' ')
	s.push(Point(p.X, p.Y-1));
      if(w[WIDTH*p.Y+p.X+1] == ' ')
	s.push(Point(p.X+1, p.Y));
      if(w[WIDTH*(p.Y+1)+p.X] == ' ')
	s.push(Point(p.X, p.Y+1));
    }

    for(int i = 0; i < lines; ++i)
      puts(&w[WIDTH*i]);
  }
  return 0;
}
