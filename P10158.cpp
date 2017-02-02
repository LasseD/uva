int find(const int x, int *parents) {
  if(x == -1)
    return -1;
  if(parents[x] != x)
    parents[x] = find(parents[x], parents);
  return parents[x];
}

void _union(int x, int y, int *parents, int *ranks) {
  int xRoot = find(x, parents);
  int yRoot = find(y, parents);
  if(xRoot == yRoot)
    return;

  // x and y are not already in same set. Merge them.
  if(ranks[xRoot] < ranks[yRoot])
    parents[xRoot] = yRoot;
  else if(ranks[xRoot] > ranks[yRoot])
    parents[yRoot] = xRoot;
  else {
    parents[yRoot] = xRoot;
    ++ranks[xRoot];
  }
}

void makeFriends(int x, int y, int *parents, int *ranks, int *enemies) {
  x = find(x, parents);
  y = find(y, parents);
  if(x == y)
    return; // no action.

  int ex = find(enemies[x], parents);
  int ey = find(enemies[y], parents);
  
  if(ex == y || ey == x) {
    //cerr << "Can't set friends because x=" << x << ", y=" << y << ", ex=" << ex << ", ey=" << ey << endl;
    cout << -1 << endl; // Enemies can't make friends
    return;
  }

  _union(x, y, parents, ranks); // Perform friendship
  enemies[find(x, parents)] = ex == -1 ? ey : ex; // Update enemy

  if(ex != -1 && ey != -1) {
    makeFriends(ex, ey, parents, ranks, enemies);
  }
}

int main() {
  int N, c, x, y, ex, ey, parents[10000], ranks[10000], enemies[10000];
  cin >> N;
  // Prepare Union-find structure (parents and ranks):
  FORI(N) {
    ranks[i] = enemies[i] = -1;
    parents[i] = i;
  }

  while(true) {
    cin >> c >> x >> y;
    if(c == 0 && x == 0 && y == 0) 
      return 0;
    //cerr << "c=" << c << ", x=" << x << ", y=" << y << endl;
    x = find(x, parents);
    y = find(y, parents);
    ex = find(enemies[x], parents);
    ey = find(enemies[y], parents);
    //cerr << "x=" << x << ", y=" << y << ", ex=" << ex << ", ey=" << ey << endl;
    if(x == y && ex != ey)
      die();
    if((x == ey) != (y == ex))
      die();
    switch(c) {
    case 1: // setFriends:
      makeFriends(x, y, parents, ranks, enemies);
      break;
    case 2: // setEnemies:
      if(x == y || (ey != -1 && ex == ey)) {
	//cerr << "Can't set enemies because x=" << x << ", y=" << y << ", ex=" << ex << ", ey=" << ey << endl;
	cout << -1 << endl; // friends can't become enemies.
	break;
      }
      enemies[x] = y;
      enemies[y] = x;
      if(ex != -1) {
	makeFriends(ex, y, parents, ranks, enemies);
      }
      if(ey != -1) {
	makeFriends(ey, x, parents, ranks, enemies);
      }
      break;
    case 3: // Are friends:
      cout << (x == y) << endl;
      break;
    case 4:
      cout << (x == ey) << endl;
      break;
    }
  }
}
