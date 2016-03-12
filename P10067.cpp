#include <iostream>
#include <set>
#include <queue>

unsigned int read4() {
  int m;
  unsigned int s = 0;
  for(int i = 0; i < 4; ++i) {
    std::cin >> m;
    s = 10*s+m;
  }
  return s;
}

int rotUp(int input, int wheel) {
  switch(wheel) {
  case 0: // singles:
    if((input % 10) == 9)
      return input-9;
    return input+1;
  case 1:
    if((input/10 % 10) == 9)
      return input-90;
    return input+10;
  case 2:
    if((input/100 % 10) == 9)
      return input-900;
    return input+100;
  default: // case 3:
    if(input >= 9000)
      return input-9000;
    return input+1000;
  }
}

int rotDown(int input, int wheel) {
  switch(wheel) {
  case 0: // singles:
    if((input % 10) == 0)
      return input+9;
    return input-1;
  case 1:
    if((input/10 % 10) == 0)
      return input+90;
    return input-10;
  case 2:
    if((input/100 % 10) == 0)
      return input+900;
    return input-100;
  default: // case 3:
    if(input < 1000)
      return input+9000;
    return input-1000;
  }
}

int main() {
  int cases, m, dist[10000];
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    for(int i = 0; i < 10000; ++i)
      dist[i] = -1;
    int s = read4();
    dist[s] = 0;
    int t = read4();
    std::set<int> forbidden;
    std::cin >> m;
    for(int i = 0; i < m; ++i)
      forbidden.insert(read4());
    std::queue<int> q;
    q.push(s);
    while(!q.empty()) {
      int top = q.front();
      if(top == t)
	break;
      q.pop();
      int newDist = dist[top]+1;
      // push all related:
      for(int i = 0; i < 4; ++i) { 
	int neighbour = rotUp(top, i);	
	if(dist[neighbour] != -1 || forbidden.find(neighbour) != forbidden.end())
	  continue;
	dist[neighbour] = newDist;
	q.push(neighbour);
      }
      for(int i = 0; i < 4; ++i) { 
	int neighbour = rotDown(top, i);	
	if(dist[neighbour] != -1 || forbidden.find(neighbour) != forbidden.end())
	  continue;	
	dist[neighbour] = newDist;
	q.push(neighbour);
      }
    }
    std::cout << dist[t] << std::endl;
  }
}
