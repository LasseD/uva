// RM (),-> from input

struct P {
  string name;
  int weight, full;
  vector<string> children;
};

typedef map<string,P*> MAP;
MAP m;

int weight(string name) {
  P *p = m[name];
  if(p->full >= 0)
    return p->full; // Done.
  FORIT(vector<string>, p->children) {
    weight(*it);
  }
  p->full = p->weight;
  FORIT(vector<string>, p->children) {
    p->full += m[*it]->full;
  }
  return p->full;
}

int main() {
  set<string> hasParent;
  string s;
  while(getline(cin, s)) {
    stringstream ss; ss << s;
    P *p = new P;
    ss >> p->name >> p->weight;
    p->full = -1;
    while(ss >> s) {
      p->children.push_back(s);
      hasParent.insert(s);
    }
    if(p->children.empty()) {
      p->full = p->weight;
    }
    if(p->children.size() == 1) {
      cerr << "Oh no! 1 child!" << endl;
    }
    m[p->name] = p;
  }
  
  FORIT(MAP, m) {
    string name = it->first;
    if(hasParent.find(name) == hasParent.end()) {
      cout << "Answer 1: " << name << endl;
    }
  }

  // Part 2 computation:
  FORIT(MAP, m) {
    P *p = it->second;
    if(p->children.empty()) {
      continue; // No children
    }
    vector<PIS> v;
    FORIT(vector<string>, p->children) {
      v.push_back(PIS(weight(*it), *it));
    }
    sort(v.begin(), v.end());
    if(v[0].first != v[1].first) {
      string toFix = v[0].second, ok = v[1].second;
      int diff = v[1].first-v[0].first;
      cout << "START Answer 2: " << (m[toFix]->weight - diff) << endl;
    }
    if(v[v.size()-1].first != v[0].first) {
      string toFix = v[v.size()-1].second, ok = v[0].second;
      int diff = v[v.size()-1].first-v[0].first;
      cout << p->name << " END Answer 2: " << (m[toFix]->weight - diff) << " fix of " << m[toFix]->name << endl;
    }    
  }
}
