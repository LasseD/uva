#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>

#define ALPHABET_SIZE 'z'-'a'+1

struct Street {
  char fromI, toI;
  int length;
};

int sp(const int sourceI, const int destI, std::vector<Street> &streets) {
  //std::cerr << "Starting dijkstra from " << (char)(sourceI+'a') << " to " << (char)(destI+'a') << std::endl;
  int dists[ALPHABET_SIZE];
  for(int i = 0; i < ALPHABET_SIZE; ++i) {
    dists[i] = -1; // unhandled locations.
  }
  dists[sourceI] = 0;

  std::vector<Street> adjacent[ALPHABET_SIZE];
  for(std::vector<Street>::const_iterator it = streets.begin(); it != streets.end(); ++it) {
    adjacent[it->fromI].push_back(*it);
    adjacent[it->toI].push_back(*it);
  }

  std::map<int,Street> cloud;
  for(std::vector<Street>::const_iterator it = adjacent[sourceI].begin(); it != adjacent[sourceI].end(); ++it) {
    Street s = *it;
    if(dists[s.fromI] == -1 || dists[s.toI] == -1) {
      cloud.insert(std::make_pair(s.length,s));
    }
  }
  while(dists[destI] == -1) {
    Street s = cloud.begin()->second;
    cloud.erase(cloud.begin());
    if(dists[s.toI] == -1) {
      dists[s.toI] = dists[s.fromI] + s.length;
      for(std::vector<Street>::const_iterator it = adjacent[s.toI].begin(); it != adjacent[s.toI].end(); ++it) {
	Street st = *it;
	if(dists[st.fromI] == -1 || dists[st.toI] == -1) {
	  cloud.insert(std::make_pair(st.length,st));
	}
      }
    }
    else if(dists[s.fromI] == -1) {
      dists[s.fromI] = dists[s.toI] + s.length;
      for(std::vector<Street>::const_iterator it = adjacent[s.fromI].begin(); it != adjacent[s.fromI].end(); ++it) {
	Street st = *it;
	if(dists[st.fromI] == -1 || dists[st.toI] == -1) {
	  cloud.insert(std::make_pair(st.length,st));
	}
      }
    }    
  }
  return dists[destI];
}

int main() {
  std::vector<Street> streets;
  int adjacentCount[ALPHABET_SIZE] = {0};
  int minAdjacent[ALPHABET_SIZE] = {0};
  int sum = 0;

  std::string street;
  while(std::cin >> street) {
    if(street == "deadend") {
      // Handle problem:
      /*
      std::cerr << "Streets in problem: " << streets.size() << std::endl;
      for(std::vector<Street>::const_iterator it = streets.begin(); it != streets.end(); ++it) {
	std::cerr << " " << it->from << "->" << it->to << ", " << it->length << std::endl;	
      }
      std::cerr << "SUM BEFORE: " << sum << std::endl;//*/
      
      // Add uneven adjacent sums:
      int uneven1 = -1;
      int uneven2 = -1;
      for(int i = 0; i < ALPHABET_SIZE; ++i) {
	if(adjacentCount[i] % 2 == 1) {
	  //std::cerr << "ADDING " << minAdjacent[i] << " for end of " << (char)(i+'a') << std::endl;
	  if(uneven1 == -1)
	    uneven1 = i;
	  else {
	    uneven2 = i;
	    break;
	  }
	}
      }
      if(uneven1 == -1) {
	// ok, done.
      }
      else if(uneven2 == -1) {
	// Just add path back from uneven1.
	sum += minAdjacent[uneven1];
      }
      else {
	sum += sp(uneven1, uneven2, streets);
      }
      
      std::cout << sum << std::endl;

      // Reset structures:
      streets.clear();      
      for(int i = 0; i < ALPHABET_SIZE; ++i) {
	adjacentCount[i] = 0;
      }
      sum = 0;
    }
    else {
      Street s;
      char fromI = s.fromI = street[0]-'a';
      char toI = s.toI = street[street.size()-1]-'a';
      int length = s.length = street.size();
      streets.push_back(s);      

      sum += length;

      adjacentCount[fromI]++;
      if(adjacentCount[fromI] == 1) {
	minAdjacent[fromI] = length;
      }
      else if(minAdjacent[fromI] > length) {
	minAdjacent[fromI] = length;
      }

      adjacentCount[toI]++;
      if(adjacentCount[toI] == 1) {
	minAdjacent[toI] = length;
      }
      else if(minAdjacent[toI] > length) {
	minAdjacent[toI] = length;
      }      
    }
  }
  return 0;
}

