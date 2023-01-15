LL registers[4] = {0,0,1,0}; // a-d. Use 0 for c in part 1

struct OP {
  string op, x, y;
};

int main() {
  OP op;
  vector<OP> ops;
  
  while(cin >> op.op) {
    if(op.op == "cpy") {
      cin >> op.x >> op.y;
    }
    else if(op.op == "inc") {
      cin >> op.x;
    }
    else if(op.op == "dec") {
      cin >> op.x;
    }
    else if(op.op == "jnz") {
      cin >> op.x >> op.y;
    }
    else {
      die();
    }
    ops.push_back(op);
  }

  int idx = 0;
  while(idx < (int)ops.size()) {
    OP op = ops[idx];
    //cout << "Line " << idx << " ";
    if(op.op == "cpy") {
      int val;
      if(op.x[0] >= 'a' && op.x[0] <= 'd') {
	val = registers[op.x[0]-'a'];
      }
      else {
	val = stoi(op.x);
      }
      registers[op.y[0]-'a'] = val;
      //cout << "COPY " << op.x << " into " << op.y << endl;
      idx++;
    }
    else if(op.op == "inc") {
      registers[op.x[0]-'a']++;
      //cout << "INC " << op.x << endl;
      idx++;
    }
    else if(op.op == "dec") {
      registers[op.x[0]-'a']--;
      //cout << "DEC " << op.x << endl;
      idx++;
    }
    else if(op.op == "jnz") {
      int inc;
      if(op.x[0] >= 'a' && op.x[0] <= 'd') {
	inc = registers[op.x[0]-'a'];
      }
      else {
	inc = stoi(op.x);
      }
      if(inc == 0)
	idx++;
      else
	idx += stoi(op.y);    
      //cout << "JUMP " << op.x << " dist " << op.y << " test " << inc << endl;
    }
    FORK(4) {
      //cout << " " << registers[k];
    }
    //cout << endl;
  }
  cout << "Answer: " << registers[0] << endl; // not 1, 42
}
