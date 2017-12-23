struct Info {
  vector<string> parts;
};

int main() {
  string s;
  GI(N); 
  getline(cin, s); // Ignore.
  string *departments = new string[N];
  deque<Info> infos[N]; // department -> deque  

  // Read departments:
  FORI(N) {
    getline(cin, departments[i]);
    // Read lines:
    while(true) {
      getline(cin, s);
      if(s.empty())
	break;
      Info info;
      int start = 0;
      FORUJ(s.size()) {
	if(s[j] != ',')
	  continue;
	s[j] = '\0';
	string part(&s[start]);
	info.parts.push_back(part);
	start = j+1;
      }
      string part(&s[start]);
      info.parts.push_back(part);
      infos[i].push_back(info);
    }
  }
  set<pair<string,int> > S;
  FORI(N)
    S.insert(make_pair(infos[i].front().parts[2], i));
  while(!S.empty()) {
    int i = S.begin()->second;
    S.erase(S.begin());
    Info info = infos[i].front();
    // Report:
    cout << "----------------------------------------" << endl;
    cout << info.parts[0] << " " << info.parts[1] << " " << info.parts[2] << endl;
    cout << info.parts[3] << endl;
    cout << "Department: " << departments[i] << endl;
    cout << "Home Phone: " << info.parts[4] << endl;
    cout << "Work Phone: " << info.parts[5] << endl;
    cout << "Campus Box: " << info.parts[6] << endl;

    infos[i].pop_front();
    if(!infos[i].empty())
      S.insert(make_pair(infos[i].front().parts[2], i));
  }
  return 0;
}
