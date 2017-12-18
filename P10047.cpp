#define INF 99999999

/*
1 out =>        +2
2 out =>        +4
3 out => +6 =>  +1
4 out => +8 =>  +3
5 out => +10 => +5
=> Don't restrict when closer than 6 from target!
 */

struct Node {
  bool blocked;
  int time[5][4];
};

// Dirs: 0=Up, right, down, left
struct Walk {
  PI pos;
  int dir, dist, time;
};

int main() {
  Node a[30][30];
  for(int cas = 1; true; ++cas) {
    GI(R); GI(C);
    if(R == 0 && C == 0)
      return 0;

    if(cas != 1)
      cout << endl;
    cout << "Case #" << cas << endl;    
    
    queue<Walk> q; // BFS through the grid to T. push, front, pop
    PI target;
    // Read grid:
    FORY(R) {
      GS(S);
      FORX(C) {
	Node &n = a[y][x];
	if(S[x] == '#') {
	  n.blocked = true;
	  continue;
	}
	n.blocked = false;
	FORJ(5) {
	  FORK(4)
	    n.time[j][k] = INF; // Mark not reached.
	}
	if(S[x] == 'S') {
	  n.time[0][0] = 0; // Start pointing up with wheel position 0.
	  Walk w; w.pos = PI(x,y); w.dist = w.dir = w.time = 0;
	  q.push(w);
	}
	else if(S[x] == 'T')
	  target = PI(x, y);
      }
    } // FORY

    // Run BFS:
    bool found = false;
    while(!q.empty()) {
      Walk w = q.front(); q.pop();
      int x = w.pos.XX;
      int y = w.pos.YY;
      Node &n = a[y][x];
      int right = (w.dir+1)%4;
      int left = (w.dir+3)%4;
      // Turn left and right:
      if(n.time[w.dist%5][right] == INF) {
	n.time[w.dist%5][right] = w.dist + 1;
	Walk w2; w2.pos = w.pos; w2.dist = w.dist; w2.dir = right; w2.time = w.time+1;
	q.push(w2);
      }
      if(n.time[w.dist%5][left] == INF) {
	n.time[w.dist%5][left] = w.dist + 1;
	Walk w2; w2.pos = w.pos; w2.dist = w.dist; w2.dir = left; w2.time = w.time+1;
	q.push(w2);
      }      
      // Walk:
      PI p2;
      switch(w.dir) {
      case 0: // Up:
	p2 = PI(x, y-1);
	break;
      case 1: // Right:
	p2 = PI(x+1, y);
	break;
      case 2: // Down:
	p2 = PI(x, y+1);
	break;
      case 3: // Left:
	p2 = PI(x-1, y);
	break;
      }
      if(p2.XX < 0 || p2.XX >= C || p2.YY < 0 || p2.YY >= R)
	continue;
      if(p2 == target && w.dist%5 == 4) {
	found = true;
	cout << "minimum time = " << w.time+1 << " sec" << endl;
	break;
      }
	
      Node &n2 = a[p2.YY][p2.XX];
      if(n2.blocked || n2.time[(w.dist+1)%5][w.dir] != INF)
	continue;
      n2.time[(w.dist+1)%5][w.dir] = w.time+1;
      Walk w2; w2.pos = p2; w2.dist = w.dist+1; w2.time = w.time+1; w2.dir = w.dir;
      q.push(w2);
    }
    if(!found)
      cout << "destination not reachable" << endl;
  } // while true
}
