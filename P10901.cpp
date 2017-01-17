#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX 10000

typedef pair<int,int> PP;

int main() {
  int cases, n, t, m, tmp;
  string s;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;
    cin >> n >> t >> m; // capacity n, travel time t, m cars to arrive.
    int *departures = new int[m];
    // Read arrivals:
    int time = 99999999;
    vector<PP> arrivalsLeft, arrivalsRight;
    for(int i = 0; i < m; ++i) {
      cin >> tmp >> s;
      if(tmp < time)
	time = tmp;
      if(s[0] == 'l')
	arrivalsLeft.push_back(PP(tmp, i));
      else
	arrivalsRight.push_back(PP(tmp, i));
    }
    vector<PP>::const_iterator itLeft = arrivalsLeft.begin();
    vector<PP>::const_iterator itRight = arrivalsRight.begin();
    
    // perform simulation:
    bool left = true; // side of ferry.
    while(itLeft != arrivalsLeft.end() || itRight != arrivalsRight.end()) {
      int onFerry = 0;
      bool anyWaitingOnOtherSide;
      if(left) {
	while(onFerry < n && itLeft != arrivalsLeft.end() && itLeft->first <= time) {
	  departures[itLeft->second] = time + t;
	  ++onFerry;
	  ++itLeft;
	}
	anyWaitingOnOtherSide = itRight != arrivalsRight.end() && itRight->first <=time;
      }
      else {
	while(onFerry < n && itRight != arrivalsRight.end() && itRight->first <= time) {
	  departures[itRight->second] = time + t;
	  ++onFerry;
	  ++itRight;
	}	
	anyWaitingOnOtherSide = itLeft != arrivalsLeft.end() && itLeft->first <=time;
      }

      if(onFerry == 0 && !anyWaitingOnOtherSide) { // Wait until there are cars:
	int nextArrival = 9999999;
	if(itLeft != arrivalsLeft.end())
	  nextArrival = itLeft->first;
	if(itRight != arrivalsRight.end() && itRight->first < nextArrival)
	  nextArrival = itRight->first;
	
	time = nextArrival;
      }
      else {
	time += t;
	left = !left;
      }
    }
    // Output:
    for(int i = 0; i < m; ++i) {
      cout << departures[i] << endl;
    }
    delete[] departures;
  } // for cas
  return 0;
}
