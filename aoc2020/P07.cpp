/*
Cleanup input:
"bags contain" -> "bag"
 */
map<string,set<string>* > m;
typedef map<string,int> MAP;

struct Bag {
  MAP content;
  LL size;
};
map<string,Bag*> bags;

bool isBag(string &s) {
  if(s.size() < 3)
    return false;
  return s[0] == 'b' && s[1] == 'a' && s[2] == 'g';
}

string getBagColor(stringstream &ss) {
  stringstream out;
  string s;
  bool first = true;
  while(ss >> s) {
    if(isBag(s)) {
      // Ensure bag exists:
      string ret = out.str();
      if(bags.find(ret) == bags.end()) {
	Bag *b2 = new Bag;
	b2->size = -1;
	bags[ret] = b2;
      }
      
      return ret;
    }
    if(first) {
      out << s;
      first = false;
    }
    else {
      out << " " << s;
    }
  }
  return NULL;
}

LL getSize(string s) {
  Bag &b = *bags[s];
  if(b.size >= 0)
    return b.size;
  LL ret = 1;
  FORIT(MAP, b.content) {
    ret += it->second * getSize(it->first);
  }
  b.size = ret;
  cout << "Size of " << s << ": " << ret << endl;
  return ret;
}

int main() {
  
  string s;
  while(getline(cin, s)) {
    stringstream ss1, ss2;
    ss1 << s;
    string b1 = getBagColor(ss1);
    int amount;
    while(ss1 >> amount) {
      string b2 = getBagColor(ss1);
      set<string> *S = new set<string>;
      if(m.find(b2) == m.end()) {
	m[b2] = S;
      }
      bags[b1]->content[b2] = amount;
      cout << b1 << " contains " << amount << " x " << b2 << endl;
      m[b2]->insert(b1);
    }
  }

  set<string> above;
  stack<string> ready;
  ready.push("shiny gold");
  above.insert("shiny gold");
  
  while(!ready.empty()) {
    string t2 = ready.top();
    ready.pop();
    if(m.find(t2) == m.end())
      continue; // Not in m!
    set<string> &S2 = *m[t2];
    FORIT(set<string>, S2) {
      s = *it;
      if(above.find(s) == above.end()) {
	ready.push(s);
      }
      above.insert(s);
    }
  }
  cout << "Answer 1: " << (int)above.size()-1 << endl;
  cout << "Answer 2: " << getSize("shiny gold")-1 << endl;
}
