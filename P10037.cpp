#include <iostream>
#include <algorithm>
#include <assert.h>
#include <vector>

int main() {
  int NUMBER_OF_CASES;
  std::cin >> NUMBER_OF_CASES;

  int people[1000];
  for(int ignore = 0; ignore < NUMBER_OF_CASES; ++ignore) {
    if(ignore != 0)
      std::cout << std::endl;

    // Parse input:
    int n;
    std::cin >> n;
    for(int i = 0; i < n; ++i) {
      std::cin >> people[i];
    }
    std::sort(&people[0], &people[n]);

    if(n == 0) {
      // Error!
      assert(false); int *die = NULL; die[0] = 666;
      return 1;
    }
    if(n == 1) {
      std::cout << people[0] << std::endl; // time
      std::cout << people[0] << std::endl;
      continue;
    }
    if(n == 2) {
      std::cout << people[1] << std::endl; // time
      std::cout << people[0] << " " << people[1] << std::endl;
      continue;
    }
    
    std::vector<int> walks;
    int time = 0;
    while(true) {
      if(n == 2) {
	// Remaining two:
	walks.push_back(people[0]);
	walks.push_back(people[1]);
	time += people[1];
	break;
      }
      if(n == 3) {
	// Push fattest:
	walks.push_back(people[0]);
	walks.push_back(people[2]);
	walks.push_back(people[0]);
	time += people[0] + people[2];
	// Remaining two:
	walks.push_back(people[0]);
	walks.push_back(people[1]);
	time += people[1];
	break;
      }
      if(people[1]+people[1] > people[n-2]+people[0]) {
	// Push last:
	walks.push_back(people[0]);
	walks.push_back(people[n-1]);
	walks.push_back(people[0]);
	time += people[0] + people[n-1];
	--n;
	continue;
      }
      // Push returner:
      walks.push_back(people[0]);
      walks.push_back(people[1]);
      walks.push_back(people[0]);
      time += people[0] + people[1];
      // Push two fattest:
      walks.push_back(people[n-1]);
      walks.push_back(people[n-2]);
      walks.push_back(people[1]);
      time += people[n-1] + people[1];      
      n-=2;
    }
    // output:
    std::cout << time << std::endl;
    bool twoWalk = true;
    for(unsigned int i = 0; i < walks.size(); i+=twoWalk?2:1, twoWalk = !twoWalk) {
      if(twoWalk) {
	std::cout << walks[i] << " " << walks[i+1] << std::endl;	
      }
      else {
	std::cout << walks[i] << std::endl;
      }      
    }
  }
  return 0;
}
