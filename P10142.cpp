#include <iostream>
#include <stdio.h>
#include <vector>
#include <assert.h>

/*
Australian Voting (Skiena)
Votes prioriticed. Count one for each top vote.
If one > 50% => win.
If not, rem all with least votes. Repeat.
Stop if winner or all tied.
 */

int readInt(const std::string line, int &pos) {
  int ret = 0;
  for(; true; ++pos) {
    char c = line[pos];
    if(c >= '0' && c <= '9') {
      ret = 10*ret + (c-'0');
    }
    else
      return ret;
  }
}

void readNInts(int n, const std::string line, int *prioritized) {
  //std::cerr << "Reading votes" << std::endl;
  int pos = 0;
  int sumA = 0;
  int sumB = 0;
  for(int i = 0; i < n; ++i) {
    while(!(line[pos] >= '0' && line[pos] <= '9')) {
      ++pos;
    }
    int priority = readInt(line, pos);
    prioritized[i] = priority-1;
    sumA+=i;
    sumB+=priority-1;
  }
  assert(sumA == sumB);
}

// Return the winner. -2 if tie, -1 if no winner.
int computeRoundVotes(int *roundVotes, int n, int voters, int *votes, int *votesI, bool *alive, int &minVotes) {
  // Reset:
  for(int i = 0; i < n; ++i)
    roundVotes[i] = 0;
  // Compute roundVotes:  
  for(int i = 0; i < voters; ++i) {
    int candidate = votes[n*i + votesI[i]];
    while(!alive[candidate]) {
      votesI[i]++;
      candidate = votes[n*i + votesI[i]];
    }
    roundVotes[candidate]++;
  }
  // Compute results:
  minVotes = 1000000;
  int maxVotes = 0;
  int winner = -1;
  int totalVotes = 0;
  for(int i = 0; i < n; ++i) {
    if(!alive[i])
      continue;
    //std::cerr << "Round votes for " << i << ": " << roundVotes[i] << std::endl;
    totalVotes += roundVotes[i];
    if(roundVotes[i] < minVotes) {
      minVotes = roundVotes[i];
    }
    if(roundVotes[i] > maxVotes) {
      winner = i;
      maxVotes = roundVotes[i];
    }
  }
  //std::cerr << "Round votes done. maxVotes=" << maxVotes << ", minVotes=" << minVotes << ", totalVotes=" << totalVotes << ", winner=" << winner << std::endl;
  if(maxVotes*2 > totalVotes) {
    return winner;
  }
  if(minVotes == maxVotes) {
    return -2;
  }
  return -1;
}

// Slow printing method. Don't copy this code...
void print(const std::string &s) {
  for(int i = 0; true; ++i) {
    if(s[i] < 32) {
      std::cout << std::endl;
      return;
    }
    std::cout << s[i];
  }
}

int main() {
  std::string line;
  std::getline(std::cin, line);
  int pos = 0;
  int NUMBER_OF_TEST_CASES = readInt(line, pos);
  std::getline(std::cin, line); // Blank line.

  int votes[20000];
  int votesI[1000];
  int roundVotes[20];
  bool alive[20];

  for(int ignore = 0; ignore < NUMBER_OF_TEST_CASES; ++ignore) {
    if(ignore > 0)
      std::cout << std::endl;

    // Parse test case input:
    std::getline(std::cin, line); // n = number of candidates.
    pos = 0;
    int n = readInt(line, pos);
    for(int i = 0; i < n; ++i)
      alive[i] = true;

    std::vector<std::string> names;
    for(int i = 0; i < n; ++i) {
      std::getline(std::cin, line); // name.
      names.push_back(line);
    }

    int voters = 0;
    while(true) {
      std::getline(std::cin, line); // votes.
      if(!(line[0] >= '0' && line[0] <= '9'))
	break;
      readNInts(n, line, &votes[n*voters]);
      votesI[voters] = 0;
      ++voters;
    }

    int winner, minVotes;
    while((winner = computeRoundVotes(roundVotes, n, voters, votes, votesI, alive, minVotes)) == -1) {
      // Kill:
      for(int i = 0; i < n; ++i) {
	if(roundVotes[i] == minVotes) {
	  alive[i] = false;
	}
      }
    }
    if(winner == -2) {      
      // Output all alive! 
      for(int i = 0; i < n; ++i) {
	if(alive[i])
	  print(names[i]);
      }
    }
    else {
      print(names[winner]);
    }
  }
}
