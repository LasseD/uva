typedef map<string,LL> MAP;
MAP m;

string s, reg1, op1, reg2, op2;
LL v1, v2;

LL get(string &reg) {
  if(m.find(reg) == m.end()) {
    return 0;
  }
  return m[reg];
}

bool check() {
  LL vReg = get(reg2);
  if(op2 == "==") {
    return vReg == v2;
  }
  else if(op2 == "!=") {
    return vReg != v2;
  }
  else if(op2 == "<=") {
    return vReg <= v2;
  }
  else if(op2 == ">=") {
    return vReg >= v2;
  }
  else if(op2 == "<") {
    return vReg < v2;
  }
  else if(op2 == ">") {
    return vReg > v2;
  }
  else {
    cerr << "Unknown op2: " << op2 << endl;
    die();
    return false;
  }  
}

int main() {
  LL ma2 = -99999999;
  while(cin >> reg1 >> op1 >> v1 >> s >> reg2 >> op2 >> v2) {
    if(check()) {
      if(op1 == "dec") {
	m[reg1] = get(reg1) - v1;
      }
      else if(op1 == "inc") {
	m[reg1] = get(reg1) + v1;
      }
      else {
	cerr << "Unknown op1: " << op1 << endl;
	die();
      }
      ma2 = max(ma2, m[reg1]);
    }
    else {
      cout << "SKIP " << reg1 << " " << op1 << " " << v1 << " " << s << " " << reg2 << " " << op2 << " " << v2 << endl;
    }	   
  }
  LL ma = -9999999;
  FORIT(MAP, m) {
    ma = max(ma, it->second);
  }  
  cout << ma << endl;
  cout << ma2 << endl;
}
