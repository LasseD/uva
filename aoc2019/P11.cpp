// Replace comma with space in input.
#define SIZE 50000000
LL v[SIZE];
int size = 0, relativeBase = 0, idx = 0, dir = 0; // 0 for up, 1 for right, 2 for down, 3 for left
PI pos(0,0);

typedef map<PI,int> MAP;
MAP m; // true for white
bool willPaint = true;

LL getInput() {
  if(m.find(pos) == m.end()) {
    cout << "Reading empty 0" << endl;
    return 0;
  }
  cout << "Reading " << m[pos] << endl;
  return m[pos];
}

void out(LL x) {
  cout << "Writing " << x << endl;
  if(willPaint) {
    m[pos] = x;
    cout << "Color " << x << " at " << pos.XX << ", " << pos.YY << endl;
  }
  else {
    if(x == 0) {
      dir = (dir+3)%4; // left
      cout << "Turned left and walked to ";
    }
    else {
      dir = (dir+1)%4; // right
      cout << "Turned right and walked to ";
    }
    switch(dir) {
    case 0:
      pos.YY--;
      break;
    case 1:
      pos.XX++;
      break;
    case 2:
      pos.YY++;
      break;
    case 3:
      pos.XX--;
      break;
    }
    cout << pos.XX << "," << pos.YY << endl;
  }
  willPaint = !willPaint;
}

int getIndex(vector<int> &modes, int param) {
  int mode = param-1 < modes.size() ? modes[param-1] : 0;
  if(idx+param < 0 || idx+param >= SIZE) {
    cerr << "PARAM RANGE " << idx << "+" << param << endl;
    die();
  }

  if(mode == 1) { // 1 => immediate mode
    return idx+param;
  }
  LL x = v[idx+param];
  if(mode == 2) { // 2 => relative mode
    if(relativeBase + x < 0 || relativeBase+x >= SIZE) {
      cerr << "RELATIVE PARAM RANGE " << relativeBase << "+" << x << endl;
      die();
    }
    return relativeBase + x;
  }
  else { // 0 => position mode
    if(x < 0 || x >= SIZE) {
      cerr << "POSITION PARAM RANGE " << x << " from " << idx << ", param " << param << endl;
      die();
    }
    return x;
  }
}

LL get(vector<int> &modes, int param) {
  return v[getIndex(modes, param)];
}

void put(vector<int> &modes, int param, LL val) {
  v[getIndex(modes, param)] = val;
}

// replace , with space in input
int main() {
  LL x;
  FORI(SIZE) {
    v[i] = 0;
  }
  while(cin >> x) {
    v[size++] = x;
  }

  m[PI(0,0)] = 1; // Part 2 only!

  while(true) {
    int opcode = v[idx]%100;
    int modeBits = v[idx]/100;
    vector<int> modes;
    while(modeBits > 0) {
      modes.push_back(modeBits % 10);
      modeBits/=10;
    }
    
    if(opcode == 1) {
      LL val = get(modes, 1) + get(modes, 2);
      put(modes, 3, val);
      idx+=4;
    }
    else if(opcode == 2) {
      LL val = get(modes, 1) * get(modes, 2);
      put(modes, 3, val);
      idx+=4;
    }
    else if(opcode == 3) {
      put(modes, 1, getInput());
      idx+=2;
    }
    else if(opcode == 4) {
      out(get(modes, 1));
      idx+=2;
    }
    else if(opcode == 5) {
      LL check = get(modes, 1);
      LL pointer = get(modes, 2);
      if(check != 0) {
	idx = pointer;
      }
      else {
	idx += 3;
      }
    }
    else if(opcode == 6) {
      LL check = get(modes, 1);
      if(check == 0) {
	idx = get(modes, 2);
      }
      else {
	idx += 3;
      }
    }
    else if(opcode == 7) {
      LL p1 = get(modes, 1);
      LL p2 = get(modes, 2);
      put(modes, 3, p1 < p2 ? 1 : 0);
      idx+=4;
    }
    else if(opcode == 8) {
      LL p1 = get(modes, 1);
      LL p2 = get(modes, 2);
      put(modes, 3, p1 == p2 ? 1 : 0);
      idx+=4;
    }
    else if(opcode == 9) {
      relativeBase += get(modes, 1);
      idx+=2;
    }
    else if(opcode == 99) {
      break;
    }
    else {
      cerr << "Unknown opcode: " << opcode << endl;
      die();
    }
  }

  // Output:
  cout << "Answer 1: " << m.size() << endl;
  int miX = 9999999, miY = 9999999, maX = -9999999, maY = -9999999;
  FORIT(MAP, m) {
    int x = it->first.XX;
    int y = it->first.YY;
    miX = min(miX, x);
    miY = min(miY, y);
    maX = max(maX, x);
    maY = max(maY, y);
  }
  for(int y = miY; y <= maY; y++) {
    for(int x = miX; x <= maX; x++) {
      if(m.find(PI(x,y)) == m.end()) {
	cout << ' ';
      }
      else {
	cout << (m[PI(x,y)] ? '#' : ' ');
      }
    }
    cout << endl;
  }
}
