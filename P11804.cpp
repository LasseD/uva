typedef pair<PI,string> PS;

int main() {
  FORCAS {
    int a, d;
    PS players[10];
    FORI(10) {
      cin >> players[i].second >> a >> d;
      players[i].first = PI(-a, d);
    }
    sort(players, players+10);
    string names[5];
    FORI(5)
      names[i] = players[i].second;
    sort(names, names+5);
    cout << "Case " << cas+1 << ":" << endl;
    cout << "(";
    FORI(5) {
      if(i != 0)
	cout << ", ";
      cout << names[i];
    }
    cout << ")" << endl << "(";
    FORI(5)
      names[i] = players[i+5].second;
    sort(names, names+5);
    FORI(5) {
      if(i != 0)
	cout << ", ";
      cout << names[i];
    }
    cout << ")" << endl;
  }
  return 0;
}
