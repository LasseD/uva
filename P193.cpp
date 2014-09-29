#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

void run(std::set<int> &unset, std::set<int> * const adjacencyList, std::vector<int> &best, std::vector<int> &black) {
  //std::cerr << "Running, |unset|=" << unset.size() << ", |black|=" << black.size() << ", |best|=" << best.size() << std::endl;
  // Find smallest number of neighbours:
  if(unset.size() <= 1) {
    if(unset.size() == 1) {
      black.push_back(*unset.begin()); // last is black
    }
    if(best.size() < black.size()) {
      best = black;
    }
    if(unset.size() == 1) {
      black.pop_back();
    }
    return;
  }

  unsigned int minNeighbours = 1000;
  std::vector<int> minSet;
  for(std::set<int>::const_iterator it = unset.begin(); it != unset.end(); ++it) {
    if(adjacencyList[*it].size() < minNeighbours) {
      minSet.clear();
      minNeighbours = adjacencyList[*it].size();
      minSet.push_back(*it);
    }
    else if(adjacencyList[*it].size() == minNeighbours) {
      if(black.size() <= 0 || (black.size() + unset.size()) < 15)
        minSet.push_back(*it);      
    }
  }
  //std::cerr << minSet.size() << " of size " << minNeighbours << std::endl; 

  // iterate through all those nodes:
  for(std::vector<int>::const_iterator it2 = minSet.begin(); it2 != minSet.end(); ++it2) {
    const int candidate = *it2;
    //std::cerr << "Testing " << candidate << std::endl;
    unset.erase(candidate); // black

    std::set<std::pair<int,int> > rem;
    std::vector<int> whites;
    for(std::set<int>::const_iterator it = adjacencyList[candidate].begin(); it != adjacencyList[candidate].end(); ++it) {
      whites.push_back(*it);
      unset.erase(*it); // white
    }

    for(std::vector<int>::const_iterator it = whites.begin(); it != whites.end(); ++it) {
      for(std::set<int>::const_iterator it3 = adjacencyList[*it].begin(); it3 != adjacencyList[*it].end(); ++it3) {
	// it3 is adjacent to white
	adjacencyList[*it3].erase(*it);
	rem.insert(std::make_pair(*it3, *it));
      }
    }
    //std::cerr << "=> 1 new black, " << whites.size() << " new white, " << rem.size() << "less edges." << std::endl;

    black.push_back(candidate);
    run(unset, adjacencyList, best, black);
    black.pop_back();

    // Re-insert:
    for(std::vector<int>::const_iterator it = whites.begin(); it != whites.end(); ++it) {
      unset.insert(*it);
    }
    unset.insert(candidate);
    for(std::set<std::pair<int,int> >::const_iterator it3 = rem.begin(); it3 != rem.end(); ++it3) {
      adjacencyList[it3->first].insert(it3->second);
    }
  }
}

/*
Heuristic: Try to color nodes with min degree black - try all.

k = |edges|
n = |nodes|
N = |tests|

black: 0, white: 1, unset: 2
 */
int main() {
  std::set<int> adjacencyList[100];  
  std::set<int> unset;  

  int N;
  std::cin >> N;
  for(int ignore = 0; ignore < N; ++ignore) {
    unset.clear();
    int n, k;
    std::cin >> n >> k;
    for(int i = 0; i < n; ++i) {
      adjacencyList[i].clear();
      unset.insert(i);
    }
    for(int i = 0; i < k; ++i) {
      int a, b;
      std::cin >> a >> b;
      --a;
      --b;
      adjacencyList[a].insert(b);
      adjacencyList[b].insert(a);
    }

    std::vector<int> best, black;
    run(unset, adjacencyList, best, black);

    std::cout << best.size() << std::endl;
    std::sort(best.begin(), best.end());
    for(unsigned int i = 0; i < best.size(); ++i) {
      if(i != 0)
	std::cout << " ";
      std::cout << (best[i]+1);
    }
    std::cout << std::endl;
  }
}
