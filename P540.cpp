#include <iostream>
#include <stdio.h>
#include <set>
#include <deque>
#include <cstring>

typedef std::pair<int,int> PP;
typedef std::set<PP> Set;
typedef std::deque<int> Deque;

int main() {
  int t, teamSize, ele;
  int *teamOfMembers = new int[1000000];
  Deque teamQueues[1000];
  char operation[100];
  for(int cas = 1; true; ++cas) {
    scanf("%d\n", &t);
    if(t == 0)
      return 0;
    std::cout << "Scenario #" << cas << std::endl;
    for(int i = 0; i < t; ++i) {
      teamQueues[i].clear();
      scanf("%d", &teamSize);
      for(int j = 0; j < teamSize; ++j) {
	scanf("%d", &ele);
	teamOfMembers[ele] = i; // set team marker for ele.
      }
      scanf("\n");
    }
    // Handle operations:
    Set set;
    int teamAddIndex = 0;
    while(true) {
      scanf("%s", operation);
      if(operation[0] == 'S') {
	scanf("\n");
	break;
      }
      else if(operation[0] == 'E') {
	scanf("%d\n", &ele);
	int team = teamOfMembers[ele];
	if(teamQueues[team].empty())
	  set.insert(PP(teamAddIndex++, team));
	teamQueues[team].push_back(ele);
      }
      else {
	int team = set.begin()->second;
	std::cout << teamQueues[team].front() << std::endl;
	teamQueues[team].pop_front();
	if(teamQueues[team].empty()) {
	  set.erase(set.begin());
	}	
	scanf("\n");
      }      
    }
    std::cout << std::endl;
  }
}
