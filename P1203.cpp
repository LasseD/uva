int main() {
  map<PI,int> s; // time, id -> generator time
  string w;
  int id, time, K;
  while(true) {
    cin >> w;
    if(w[0] == '#')
      break;
    cin >> id >> time;
    s[PI(time,id)] = time;
  }
  cin >> K;
  FORI(K) {
    map<PI,int>::iterator it = s.begin();
    id = it->first.second;
    time = it->second;
    cout << id << endl;

    int newTime = it->first.first + time;    
    s.erase(it);
    s[PI(newTime,id)] = time;
  }
  return 0;
}
