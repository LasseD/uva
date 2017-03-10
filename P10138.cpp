typedef pair<bool,int> InOutDist;
typedef pair<long,InOutDist> TimeToInOutDist;

long parseTime(string &s) {
  long ret = 100*100*(10*(s[3]-'0')+s[4]-'0');
  ret += 100*(10*(s[6]-'0')+s[7]-'0');
  ret += (10*(s[9]-'0')+s[10]-'0');
  return ret;
}

int main() {
  vector<TimeToInOutDist> data[1000]; // ID -> data
  string line, plate, time, enter;
  int dist;
  getline(cin, line);
  stringstream ss1; ss1 << line; int cases; ss1 >> cases;
  getline(cin, line);
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      printf("\n");

    getline(cin, line);
    stringstream ss2; ss2 << line;
    int prices[24];
    FORI(24)
      ss2 >> prices[i];
    map<string,int> CarId; // license plate -> ID
    
    // Read data:
    while(getline(cin, line)) {
      stringstream ss3; ss3 << line;
      if(!(ss3 >> plate >> time >> enter >> dist))
	break;
      if(CarId.find(plate) == CarId.end()) {
	data[CarId.size()].clear();
	CarId.insert(make_pair(plate, (int)CarId.size()));
      }
      data[CarId[plate]].push_back(TimeToInOutDist(parseTime(time), InOutDist(enter[1] == 'n', dist)));
    }    
    
    // Handle all cars in ascending order:
    for(map<string,int>::const_iterator it = CarId.begin(); it != CarId.end(); ++it) {
      //cerr << "Handling " << it->first << endl;
      vector<TimeToInOutDist> &d = data[it->second];
      sort(d.begin(),d.end()); // sort by time
      int billInCents = 0;
      long lastEnterTime = -1;
      int lastEnterDist = -1;
      FORIT2(vector<TimeToInOutDist>, d) {
	bool in = it2->second.first;
	dist = it2->second.second;
	if(in) {
	  lastEnterTime = it2->first;
	  lastEnterDist = dist;
	  //cerr << " in at time " << lastEnterTime << ", dist " << dist << endl;
	}
	else {
	  //cerr << " out at time " << it2->first << ", dist " << dist << endl;
	  if(lastEnterTime == -1)
	    continue;
	  int deltaDist = ABS(dist-lastEnterDist);
	  billInCents += 100 + deltaDist * prices[(lastEnterTime/100)%100];
	  lastEnterTime = -1;
	}
      }
      if(billInCents > 0) {
	billInCents += 200;
	printf("%s $%.2lf\n", it->first.c_str(), billInCents/100.0);
      }
    }

  }
  return 0;
}
