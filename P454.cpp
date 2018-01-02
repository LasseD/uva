string makeAna(const string &s) {
  string copy(s);
  sort(copy.begin(), copy.end());
  return copy;
}

int main() {
  string line, s, ana;
  FORCAS {
    if(cas == 0) {
      getline(cin, line);
      getline(cin, line);
    }
    else
      cout << endl;
    vector<PS> v;
    while(getline(cin, line)) {
      stringstream ss1, ss2; ss1 << line;
      int parts = 0;
      while(ss1 >> s) {
	++parts;
	ss2 << s;
      }
      if(parts == 0)
	break;
      ss2 >> s;
      ana = makeAna(s);
      v.push_back(PS(line, ana));
    }
    sort(v.begin(), v.end());
    FORUI(v.size()) {
      for(unsigned int j = i+1; j < v.size(); ++j)
	if(v[i].P2 == v[j].P2)
	  cout << v[i].P1 << " = " << v[j].P1 << endl;
    }
  }
  return 0;
}
