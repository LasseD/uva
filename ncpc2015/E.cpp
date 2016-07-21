#include <iostream>
#include <ctype.h>
#include <map>
#include <algorithm>

typedef std::pair<int,int> show;

int main() {
  int n, k, xi, yi;
  show *shows = new show[n];

  std::cin >> n >> k;

  std::map<int,int> machine;
  machine.insert(show(0,k)); // Misuse

  for(int i = 0; i < n; ++i) {
    std::cin >> xi >> yi;
    if(xi == yi)
      while(true)
	; // assert false.
    shows[i] = show(yi,xi); // end time, start time - easy sort.
  }
  std::sort(shows, shows+n);
  
  int count = 0;
  for(int i = 0; i < n; ++i) {
    show s = shows[i];
    int startTime = s.second;
    int endTime = s.first;

    std::map<int,int>::iterator it = machine.upper_bound(startTime);
    if(it == machine.begin()) {
      continue; // No update.
    }
    --it;
    if(it->first > startTime) {
      while(true)
	; // assert(false);
    }
    int currCount = it->second;
    int currTime = it->first;
    machine.erase(it->first);
    if(currCount != 1) {
      machine.insert(show(currTime, currCount-1));
    }

    it = machine.find(endTime);
    if(it == machine.end()) {
      machine.insert(show(endTime, 1));
    }
    else {
      currCount = it->second;
      machine.erase(it->first);
      machine.insert(show(endTime, currCount+1));
    }
    ++count;
  }
  std::cout << count << std::endl;
}

