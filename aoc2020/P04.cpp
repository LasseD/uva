typedef map<string,string> MAP;

string fields[8] = {"byr","iyr","eyr","hgt","hcl","ecl","pid","cid"};
MAP m;
set<string> eyes;

bool isInt(string &s) {
  FORUI(s.size()) {
    char c = s[i];
    if(!(c >= '0' && c <= '9')) {
      return false;
    }
  }
  return true;
}

bool isHex(char c) {
  return ('0' <= c && c <= '9') || ('a' <= c && c <= 'f');
}

bool inRange(int low, int high, string &s) {
  if(!isInt(s))
    return false;
  int y = stoi(s);
  return low <= y && y <= high;
}

bool endsWith(string &s, string end) {
    if(end.size() > s.size())
      return false;
    return equal(end.rbegin(), end.rend(), s.rbegin());
}

bool check() {
  FORI(8) {
    string k = fields[i];
    if(m.find(k) == m.end()) {
      if(k == "cid") {
	continue;
      }
      else {
	cout << "FAIL MISSING " << k << endl;
	return false;
      }
    }
    string v = m[k];
    if(k == "byr") {
      if(!inRange(1920, 2002, v)) {
	cout << "FAIL byr " << v << endl;
	return false;
      }
    }
    else if(k == "iyr") {
      if(!inRange(2010, 2020, v)) {
	cout << "FAIL iyr " << v << endl;
	return false;
      }
    }
    else if(k == "eyr") {
      if(!inRange(2020, 2030, v)) {
	cout << "FAIL eyr " << v << endl;
	return false;
      }
    }
    else if(k == "hgt") {
      if(endsWith(v, "cm")) {
	v = v.substr(0, v.size()-2);
	if(!inRange(150, 193, v)) {
	  cout << "FAIL Height in cm: " << v << endl;
	  return false;
	}
      }
      else if(endsWith(v, "in")) {
	v = v.substr(0, v.size()-2);
	if(!inRange(59, 76, v)) {
	  cout << "FAIL Height in in: " << v << endl;
	  return false;
	}
      }
      else
	return false;
    }
    else if(k == "hcl") {
      if(v[0] != '#' || v.size() != 7) {
	cout << "FAIL hcl missing #: " << v << endl;
	return false;
      }
      FORJ(6) {
	if(!isHex(v[j+1])) {
	  cout << "FAIL hcl hex: " << v << endl;
	  return false;
	}
      }
    }
    else if(k == "ecl") {      
      if(eyes.find(v) == eyes.end()) {
	cout << "FAIL unknown eye color: " << v << endl;
	return false;
      }
    }
    else if(k == "pid") {
      if(v.size() != 9 || !isInt(v)) {
	cout << "FAIL pid: " << v << endl;
	return false;
      }
    }		   
  }
  return true;
}

// Remove : from input
int main() {
  int answer = 0;

  eyes.insert("amb");
  eyes.insert("blu");
  eyes.insert("brn");
  eyes.insert("gry");
  eyes.insert("grn");
  eyes.insert("hzl");
  eyes.insert("oth");
  
  string line, k, v;
  while(true) {
    bool hasLine = getline(cin, line);
    if(!hasLine || line == "") {
      if(check())
	answer++;
      m.clear();
    }
    if(!hasLine) {
      cout << answer << endl;
      return 0;
    }
    if(line == "") {
      continue;
    }
    stringstream ss; ss << line;
    while(ss >> k >> v) {
      m[k] = v;
    }
  } // while true
}
