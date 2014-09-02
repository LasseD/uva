#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

typedef unsigned long long ul;

#define NUMBER_OF_PRIMES 25

// number of primes: 25.
int primes[25] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};

//  int multipliers[NUMBER_OF_PRIMES];
void factorizeFaculty(int * const multipliers, int N) {
  for(int i = 0; i < NUMBER_OF_PRIMES; ++i) {
    multipliers[i] = 0;
  }
  if(N == 1)
    return;
  // mult up:
  for(int i = 2; i <= N; ++i) {
    int remainder = i;
    int primeIndex = 0;
    while(remainder > 1) {
      while(remainder % primes[primeIndex] == 0) {
	multipliers[primeIndex]++;
	remainder /= primes[primeIndex];
      }
      ++primeIndex;
    }
  }
} 

ul facDiv(int N, std::vector<int> divs) {
  int multipliers[NUMBER_OF_PRIMES];
  factorizeFaculty(multipliers, N);

  for(unsigned int i = 0; i < divs.size(); ++i){
    int M = divs[i];
    int m2[NUMBER_OF_PRIMES];
    factorizeFaculty(m2, M);

    for(int j = 0; j < NUMBER_OF_PRIMES; ++j) {
      multipliers[j] -= m2[j];
    }
  }

  ul res = 1;
  for(int i = 0; i < NUMBER_OF_PRIMES; ++i) {
    if(multipliers[i] > 0) {
      for(int j = 0; j < multipliers[i]; ++j)
	res *= primes[i];
    }
  }
  return res;
}

ul combinationsSorted(std::string s) {
  int topFac = s.size();
  std::vector<int> divs;
  for(unsigned int i = 0; i < s.size()-1;) {
    unsigned int j = i;
    while(j < s.size()-1 && s[j+1] == s[i]) {
      ++j;
    }
    divs.push_back(j-i+1);
    i = j+1;
  }
  ul base = facDiv(topFac, divs);
  return base;
}

ul combinationsTo(std::string s, char upTo) {
  char *w = new char[s.size()];  
  w[s.size()-1] = '\0';
  ul res = 0;
  for(unsigned int i = 0; true; ++i) {
    if(i == s.size())
      throw std::exception();
    if(s[i] == upTo) {
      break;
    }
    if(i > 0 && s[i] == s[i-1])
      continue; // skip duplicates
    // make w:
    if(i > 0) {
      for(unsigned int j = 0; j < i; ++j) {
        w[j] = s[j];
      }
    }
    for(unsigned int j = i+1; j < s.size(); ++j) {
      w[j-1] = s[j];
    }
    // count:
    res += combinationsSorted(std::string(w));
  }
  delete[] w;
  return res;
}

std::string rm(std::string s, char c) {
  char *res = new char[s.size()];
  res[s.size()-1] = '\0';
  unsigned int i = 0;
  for(; i < s.size(); ++i) {
    if(s[i] == c)
      break;
    res[i] = s[i];
  }
  while(++i < s.size()) {
    res[i-1] = s[i];
  }
  std::string r(res);
  delete[] res;
  return r;
}

int main() {
  while(true) {
    std::string query;
    std::string sorted;
    std::string remainder;

    std::cin >> query;
    if(query[0] == '#')
      return 0;

    sorted = query;
    std::sort(sorted.begin(), sorted.end());
    remainder = sorted;

    //std::cerr << "Query: " << query << " sorted " << sorted << std::endl;
    ul res = 1;
    for(unsigned int i = 0; i < query.size(); ++i) {
      res += combinationsTo(remainder, query[i]);
      remainder = rm(remainder, query[i]);
    }
    printf("%10llu\n", res);
  }
}
