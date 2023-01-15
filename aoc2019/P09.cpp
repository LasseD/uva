#define SIZE 50000000
LL v[SIZE];
vector<LL> input, output;
int inputIdx = 0, size = 0, relativeBase = 0, idx = 0;

LL getInput() {
  if(inputIdx >= 1)
    die();
  return input[inputIdx++];
}

void out(LL x) {
  output.push_back(x);
  cout << "Output: " << x << endl;
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

  input.push_back(2); // 1 for part 1

  cout << "Setup complete" << endl;
      
  while(true) {
    int opcode = v[idx]%100;
    //cout << idx << " OP " << opcode << " parameter modes:";
    int modeBits = v[idx]/100;
    vector<int> modes;
    while(modeBits > 0) {
      //cout << " " << modeBits%10;
      modes.push_back(modeBits % 10);
      modeBits/=10;
    }
    //cout << endl;
    
    if(opcode == 1) {
      LL val = get(modes, 1) + get(modes, 2);
      //cerr << "Putting value " << val << " to position " << v[idx+3] << endl;
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
}
