// RM "Guard #" and "[1518-". Replace :-] with space
int cntOnes(ULL x) {
  int ret = 0;
  while(x > 0) {
    if((x & 1) == 1) {
      ret++;
    }
    x >>= 1;
  }
  return ret;
}
typedef map<int,int> MAP;
int main() {
  // Sort input:
  vector<string> v;
  string s;
  while(getline(cin, s)) {
    v.push_back(s);
  }
  sort(v.begin(), v.end());

  // Analyse:
  vector<PULL> v2; // id -> asleep
  MAP m; // id -> total sleep
  
  int month = -1, day = -1, hour = -1, minute = -1, guard = -1;
  ULL sleep = 0;
  FORIT(vector<string>, v) {
    stringstream ss; ss << *it;
    //cout << *it << endl;
    ss >> month >> day >> hour >> minute >> s;
    if(s == "falls") {
      if(hour != 0) {
	cerr << "Unexpected hour: " << hour << endl;
	die();
      }
      for(int i = minute; i <= 59; i++) {
	sleep |= ((ULL)1 << i);
      }
    }
    else if(s == "wakes") {
      if(hour != 0) {
	cerr << "Unexpected hour: " << hour << endl;
	die();
      }
      for(int i = minute; i <= 59; i++) {
	sleep &= ~((ULL)1 << i);
      }
    }
    else {
      if(guard != -1) {
	cout << guard << ": " << bitset<60>(sleep) << endl;
	v2.push_back(PULL(guard,sleep));
	m[guard]+=cntOnes(sleep);
      }
      
      guard = stoi(s);
      if(m.find(guard) == m.end())
	m[guard] = 0;
      sleep = 0;
      if(hour != 0) {
	day++;
      }
    }
  }
  cout << guard << ": " << bitset<60>(sleep) << endl;
  v2.push_back(PULL(guard,sleep));
  m[guard]+=cntOnes(sleep);  

  // Find sleepiest guard:
  int bestGuard = -1;
  int bestSleep = -1;
  FORIT(MAP, m) {
    if(bestSleep < it->second) {
      bestGuard = it->first;
      bestSleep = it->second;
    }
  }
  cout << "Guard to kill: " << bestGuard << endl;
  // Find when to kill:
  int minutes[60];
  FORI(60)
    minutes[i] = 0;
  
  FORIT(vector<PULL>, v2) {
    if(it->first != bestGuard) {
      continue; // Not our guy!
    }
    ULL bits = it->second;
    FORI(60) {
      if((bits & 1) == 1) {
	minutes[i]++;
      }
      bits >>= 1;
    }
  }
  int bestMinute = -1;
  int mostSleep = -1;
  FORI(60) {
    if(minutes[i] > mostSleep) {
      bestMinute = i;
      mostSleep = minutes[i];
    }
  }
  cout << "Most sleep at minute " << bestMinute << ": " << mostSleep << endl;
  cout << "Answer 1: " << (bestGuard * bestMinute) << endl;

  // Part 2:
  bestMinute = -1;
  int sleepAtMinute = -1;
  int guardAtMinute = -1;
  FORI(60) { // minute i
    FORIT(MAP, m) { // Try each guard:
      int guard = it->first;
      int sleep = 0;
      FORIT(vector<PULL>, v2) { // See if they slept:
	if(it->first != guard) {
	  continue; // Not our guy!
	}
	ULL bits = it->second;
	if(((bits >> i) & 1) == 1) {
	  sleep++;
	}
      }
      if(sleep > sleepAtMinute) {
	bestMinute = i;
	sleepAtMinute = sleep;
	guardAtMinute = guard;
      }
    }
  }
  cout << "Guard " << guardAtMinute << " Sleeps " << sleepAtMinute << " at " << bestMinute << endl;
  cout << "Answer 2: " << (guardAtMinute * bestMinute) << endl;
}
