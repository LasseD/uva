#define SIZE 100000
LL v[SIZE];
vector<LL> input, output;
int inputIdx = 0, size = 0;

LL getInput() {
  return input[inputIdx++];
}

void out(LL x) {
  output.push_back(x);
  cout << "Output: " << x << endl;
}

LL get(vector<int> &modes, int param, int idx) {
  int mode = param-1 < modes.size() ? modes[param-1] : 0;
  if(idx+param < 0 || idx+param >= size) {
    cerr << "Parameter out of bounds: " << idx << " + " << param << endl;
    die();
  }
  LL x = v[idx+param];
  if(mode == 1) { // 1 => immediate mode
    return x;
  }
  else { // 0 => position mode
    if(x < 0 || x >= size) {
      cerr << "Position mode parameter out of bounds: " << x << endl;
      die();
    }
    return v[x];
  }
}

// replace , with space in input
int main() {
  LL x;
  while(cin >> x) {
    v[size++] = x;
  }

  input.push_back(5); // 1 for part 1, 5 for part 2.
  
  int idx = 0;
  cout << "Setup complete" << endl;
      
  while(true) {
    int opcode = v[idx]%100;
    //cout << "OP " << opcode;
    int modeBits = v[idx]/100;
    vector<int> modes;
    while(modeBits > 0) {
      //cout << " " << modeBits%2;
      modes.push_back(modeBits % 2);
      modeBits/=10;
    }
    //cout << endl;
    
    if(opcode == 1) {
      LL val = get(modes, 1, idx) + get(modes, 2, idx);
      //cerr << "Setting value " << val << " to position " << v[idx+3] << endl;
      v[v[idx+3]] = val;
      idx+=4;
    }
    else if(opcode == 2) {
      v[v[idx+3]] = get(modes, 1, idx) * get(modes, 2, idx);
      idx+=4;
    }
    else if(opcode == 3) {
      v[v[idx+1]] = getInput();
      cout << "Reading input " << v[v[idx+1]] << endl;
      idx+=2;
    }
    else if(opcode == 4) {
      out(get(modes, 1, idx));
      idx+=2;
    }
    else if(opcode == 5) {
      LL check = get(modes, 1, idx);
      LL pointer = get(modes, 2, idx);
      if(check != 0) {
	cout << "Jump !0 " << pointer << endl;
	idx = pointer;
      }
      else {
	idx+=3;
      }
    }
    else if(opcode == 6) {
      LL check = get(modes, 1, idx);
      LL pointer = get(modes, 2, idx);
      if(check == 0) {
	cout << "Jump 0 " << pointer << endl;
	idx = pointer;
      }
      else {
	idx+=3;
      }
    }
    else if(opcode == 7) {
      LL p1 = get(modes, 1, idx);
      LL p2 = get(modes, 2, idx);
      v[v[idx+3]] = p1 < p2 ? 1 : 0;
      idx+=4;
    }
    else if(opcode == 8) {
      LL p1 = get(modes, 1, idx);
      LL p2 = get(modes, 2, idx);
      v[v[idx+3]] = p1 == p2 ? 1 : 0;
      idx+=4;
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
