#include <iostream>
#include <vector>

using namespace std;

int main() {
  int cases, ferryLength, numCars, tmp;
  string s;
  std::cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    cin >> ferryLength >> numCars;
    ferryLength *= 100; // in cm.
    int ret = 0;
    vector<int> arrivalsLeft, arrivalsRight;
    for(int i = 0; i < numCars; ++i) {
      cin >> tmp >> s;
      if(s[0] == 'l')
	arrivalsLeft.push_back(tmp);
      else
	arrivalsRight.push_back(tmp);
    }
    vector<int>::const_iterator itLeft = arrivalsLeft.begin();
    vector<int>::const_iterator itRight = arrivalsRight.begin();
    
    // perform simulation:
    bool left = true; // side of ferry.
    while(itLeft != arrivalsLeft.end() || itRight != arrivalsRight.end()) {
      int onFerry = 0;
      if(left) {
	while(itLeft != arrivalsLeft.end() && onFerry + *itLeft <= ferryLength) {
	  onFerry += *itLeft;
	  ++itLeft;
	}
      }
      else {
	while(itRight != arrivalsRight.end() && onFerry + *itRight <= ferryLength) {
	  onFerry += *itRight;
	  ++itRight;
	}
      }

      ++ret;
      left = !left;
    }
    // Output:
    cout << ret << endl;
  } // for cas
  return 0;
}
