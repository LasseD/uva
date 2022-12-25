struct Item {
  bool isList, isDivider;
  int v;
  vector<Item*> e;
};

std::ostream &operator<<(std::ostream &os, Item const &x) {
  if(x.isList) {
    os << '[';
    FORUI(x.e.size()) {
      if(i > 0)
	os << ',';
      os << *x.e[i];
    }
    os << ']';
  }
  else {
    cout << x.v;
  }
  return os;
}

void parse(string s, Item &item) {
  //cout << " Parsing " << s << endl;
  if(s == "[]") {
    // Empty string!
    item.isList = true;
  }
  else if(s[0] == '[') {
    item.isList = true;
    // Parse items
    int lv = 0;
    int from = 1, to = 1;
    while(to < s.size()-1) {
      if(s[to] == '[') {
	lv++;
	to++;
      }
      else if(s[to] == ']') {
	lv--;
	to++;
      }
      else if(s[to] == ',' && lv == 0) {
	Item *x = new Item();
	parse(string(s, from, to-from), *x);
	item.e.push_back(x);
	to = from = to + 1;
      }
      else {
	to++;
      }
    }
    // Last element:
    Item *x = new Item();
    parse(string(s, from, to-from), *x);
    item.e.push_back(x);

  }
  else {
    //cout << " Expecting int: " << s << endl;
    item.isList = false;
    item.v = stoi(s);
  }
}

int lt(Item &a, Item &b) {
  if(!a.isList && !b.isList) {
    return a.v < b.v;
  }
  else if(!a.isList) {
    Item tmp;
    tmp.isList = true;
    tmp.e.push_back(&a);
    return lt(tmp, b);
  }
  else if(!b.isList) {
    Item tmp;
    tmp.isList = true;
    tmp.e.push_back(&b);
    return lt(a, tmp);
  }
  else {
    FORI(min(a.e.size(), b.e.size())) {
      Item *aa = a.e[i];
      Item *bb = b.e[i];
      if(lt(*aa, *bb))
	return true;
      if(lt(*bb, *aa))
	return false;
      // else continue to next
    }
    return a.e.size() < b.e.size();
  }
}

int main() {
  int answer1 = 0;

  Item v[450];
  
  string a, b;
  int idx = 1, idx2 = 0;
  while(getline(cin, a) && getline(cin, b)) {
    Item &la = v[idx2++];
    Item &lb = v[idx2++];
    la.isDivider = lb.isDivider = false;
    parse(a, la);
    cout << "Parsed A " << la << endl;
    parse(b, lb);
    cout << "Parsed B " << lb << endl;

    if(lt(la, lb)) {
      cout << "LT! " << idx << endl;
      answer1 += idx;
    }

    if(!getline(cin, a)) {
      break; // No empty line
    }
    idx++;
  }

  // Add dividers
  Item &d1 = v[idx2++];
  Item &d2 = v[idx2++];

  d1.isDivider = d2.isDivider = true;
  parse("[[2]]", d1);
  parse("[[6]]", d2);

  sort(v, v+idx2, lt);
  vector<int> w;
  FORI(idx2) {
    if(v[i].isDivider)
      w.push_back(i+1);
  }
  
  
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << (w[0]*w[1]) << endl;
} // int main
