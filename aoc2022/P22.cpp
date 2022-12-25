#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3

string M[252];
int W, H = 0, W2, H2;
PI p(0,0);
int dist = 0;
int dir = 0; // Initially right

char get(int x, int y) {
  if(x < 0 || y < 0 || x >= W || y >= H) {
    return ' ';
  }
  string s=M[y];
  if(x >= (int)s.size()) {
    return ' ';
  }
  return s[x];
}
char get() {
  return get(p.XX, p.YY);
}
void put(char c) {
  M[p.YY][p.XX] = c;
}

void walk1() {
  int x, y;
  switch(dir) {
  case 0: // Right:
    put('>');
    x = p.XX+1;
    if(get(x, p.YY) == ' ') { // wrap      
      x = 0;
      while(get(x,p.YY) == ' ')
	x++;
    }
    if(get(x, p.YY) == '#')
      return; // Can't walk
    p.XX = x;
    break;
  case 2: // Left:
    put('<');
    x = p.XX-1;
    if(get(x, p.YY) == ' ') { // wrap
      x = W-1;
      while(get(x,p.YY) == ' ')
	x--;
    }
    if(get(x, p.YY) == '#')
      return; // Can't walk
    p.XX = x;
    break;    
  case 1: // Down:
    put('v');
    y = p.YY+1;
    if(get(p.XX, y) == ' ') { // wrap
      y = 0;
      while(get(p.XX, y) == ' ')
	y++;
    }
    if(get(p.XX, y) == '#')
      return; // Can't walk
    p.YY = y;
    break;
  case 3: // Up:
    put('^');
    y = p.YY-1;
    if(get(p.XX, y) == ' ') { // wrap
      y = H-1;
      while(get(p.XX, y) == ' ')
	y--;
    }
    if(get(p.XX, y) == '#')
      return; // Can't walk
    p.YY = y;
    break;
  default:
    cerr << "Unexpected direction: " << dir << " when walking from " << p.XX << ", " << p.YY << endl;
    die();
  }  
}

void walk() {
  //cout << " Walk " << dist << " in direction " << dir << endl;
  FORI(dist) {
    walk1();
  }
  dist = 0;
}

void atLast(int x, int y, int newDir) {
  if(newDir < 0)
    die(); // Nope
  char c = get(x, y);
  if(c == ' ') {
    cerr << "VOID STEP! " << x << ", " << y << endl;
    die();
  }
  if(c == '#') {
    return;
  }
  p.XX = x;
  p.YY = y;
  dir = newDir;
}

void walkRight() {
  //cout << "Right" << endl;
  int x = p.XX+1, y=p.YY;
  if(get(x, p.YY) == '#')
    return; // No walk :)
  if(get(x, p.YY) != ' ') {
    put('>');
    p.XX = x;
    return; // Normal walk :)
  }
  int newDir = -1;
  switch(y / H2) {
  case 0: // Wrap to 1,2 <
    x = 2 * W2 -1;
    y = 3*H2 - y - 1;
    newDir = LEFT; // Left
    break;
  case 1: // Wrap to 2,0
    x = y + W2;
    y = H2-1;
    newDir = UP; // Up
    break;
  case 2: // Wrap to 2, 0 <
    x = 3*W2-1;
    y = H2-(y-2*H2)-1;
    newDir = LEFT;
    break;
  case 3: // Wrap to 1, 2 ^
    x = y-2*H2;
    y = 3*H2-1;
    newDir = UP;
    break;
  default:
    die();
  }
  put('>');
  atLast(x, y, newDir);
}

void walkLeft() {
  //cout << "Left" << endl;
  int x = p.XX-1, y=p.YY;
  if(get(x, p.YY) == '#')
    return; // No walk :)
  if(get(x, p.YY) != ' ') {
    put('<');
    p.XX = x;
    return; // Normal walk :)
  }
  int newDir = -1;
  cout << "WARP LEFT " << (y/H2) << endl;
  switch(y / H2) {
  case 0: // Wrap to 0, 3 >
    x = 0;
    y = 3*H2 - y - 1;
    newDir = RIGHT;
    break;
  case 1: // Wrap to 0, 2 v 
    x = y-H2;
    y = 2*H2;
    newDir = DOWN;
    break;
  case 2: // Wrap to 1, 0 >
    x = W2;
    y = H2 - 1 - (y-2*H2);
    newDir = RIGHT;
    break;
  case 3: // Wrap to 1, 0 v
    x = y-3*H2 + W2;
    y = 0;
    newDir = DOWN;
    break;
  default:
    die();
  }
  put('<');
  atLast(x, y, newDir);
}

void walkDown() {
  //cout << "Down" << endl;
  int x = p.XX, y=p.YY+1;
  if(get(x, y) == '#')
    return; // No walk :)
  if(get(x, y) != ' ') {
    put('v');
    p.YY = y;
    return; // Normal walk :)
  }
  int newDir = -1;
  cout << "WARP DOWN " << (x/W2) << endl;
  switch(x / W2) {
  case 0: // Wrap to 2, 0 v
    x = 2*W2 + x;
    y = 0;
    newDir = DOWN;
    break;
  case 1: // to 0, 3 <
    y = 3*H2 + x - W2;
    x = W2-1;
    newDir = LEFT;
    break;
  case 2: // to 1, 1 <
    y = H2 + x - 2*W2;
    x = 2*W2-1;
    newDir = LEFT;
    break;
  default:
    die();
  }
  put('v');
  atLast(x, y, newDir);
}

void walkUp() {
  //cout << "Up" << endl;
  int x = p.XX, y=p.YY-1;
  if(get(x, y) == '#') {
    return; // No walk :)
  }
  if(get(x, y) != ' ') {
    put('^');
    p.YY = y;
    cout << "NORMAL UP " << y << endl;
    return; // Normal walk :)
  }
  int newDir = -1;
  cout << "WARP UP " << (x/W2) << endl;
  switch(x / W2) {
  case 0: // to 1, 1 >
    y = x + H2;
    x = W2;
    newDir = RIGHT;
    break;
  case 1: // to 0, 3 >
    y = x - W2 + 3 * H2;
    x = 0;
    newDir = RIGHT;
    break;
  case 2: // to 0, 3 ^
    x = x - 2*W2;
    y = 4*H2-1;
    newDir = UP;
    break;
  default:
    die();
  }
  put('^');
  atLast(x, y, newDir);
}

void walk2() {
  cout << " Walk " << dist << " in direction " << dir << endl;
  FORI(dist) {
    switch(dir) {
    case RIGHT:
      walkRight();
      break;
    case DOWN:
      walkDown();
      break;
    case LEFT:
      walkLeft();
      break;
    case UP:
      walkUp();
      break;      
    }
  }
  put('X');
  dist = 0;
}

int main() {
  // Scan map:
  while(getline(cin, M[H])) {
    if(M[H] == "")
      break;
    W = max(W, (int)M[H].size());
    H++;
  }
  cout << "Map scanned " << W << " x " << H << endl;

  GS(S); // Code
  p.XX = 0;
  while(get() == ' ') {
    p.XX++; // Step out of void
  }

  /* Part 1:
  // Walk:
  FORUI(S.size()) {
    char c = S[i];
    switch(c) {
    case 'R':
      walk();
      dir = (dir+1)%4;
      break;
    case 'L':
      walk();
      dir = (dir+3)%4;
      break;
    default:
      dist =  10*dist + (c-'0');
      break;
    }
  }
  walk();
  FORI(H) {
    cout << M[i] << endl;
  }  
  cout << "Walked to " << (p.XX+1) << ", " << (p.YY+1) << " dir " << dir << endl;
  cout << "Answer 1: " << (1000*(p.YY+1) + 4*(p.XX+1) + dir) << endl;
  */

  // Answer 2:
  W2 = W/3;
  H2 = H/4;

  // Walk:
  FORUI(S.size()) {
    char c = S[i];
    switch(c) {
    case 'R':
      walk2();
      dir = (dir+1)%4;
      break;
    case 'L':
      walk2();
      dir = (dir+3)%4;
      break;
    default:
      dist =  10*dist + (c-'0');
      break;
    }
  }
  walk2();
  FORI(H) {
    cout << M[i] << endl;
  }
  cout << endl;
  cout << "Walked to " << (p.XX+1) << ", " << (p.YY+1) << " dir " << dir << endl;
  cout << "Answer 2: " << (1000*(p.YY+1) + 4*(p.XX+1) + dir) << endl;
}
