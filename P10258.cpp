#include <iostream>
#include <stdio.h>
#include <vector>
#include <tuple>
#include <algorithm>

typedef std::vector<std::tuple<int,int,int> > Vec;

int nextInt(char *w, int &idx) {
  char c;
  while(!isdigit(c = w[idx++]))
    if(!isprint(c))
      return -1;
  int ret = c-'0';
  while(isdigit(c = w[idx++]))
    ret = 10*ret + c-'0';
  return ret;
}
char nextChar(char *w, int &idx) {
  char c;
  while(!isalpha(c = w[idx++]))
    if(!isprint(c))
      return -1;
  return c;
}

struct Contestant {
  int incorrect[9];
  int correctTimes[9];
  bool anySubmissions;

  void addOther() {
    anySubmissions = true;
  }
  void addIncorrect(int problem) {
    if(correctTimes[problem] >= 0)
      return;
    ++incorrect[problem];
    anySubmissions = true;
  }
  void addCorrect(int problem, int time) {
    if(correctTimes[problem] >= 0)
      return;
    correctTimes[problem] = time;
    anySubmissions = true;
  }
  void reset() {
    for(int i = 0; i < 9; ++i) {
      incorrect[i] = 0;
      correctTimes[i] = -1;
    }
    anySubmissions = false;
  }
  int countCorrect() {
    int ret = 0;
    for(int i = 0; i < 9; ++i) {
      if(correctTimes[i] != -1)
	++ret;
    }
    return ret;
  }
  int penalty() {
    int ret = 0;
    for(int i = 0; i < 9; ++i) {
      if(correctTimes[i] == -1)
	continue;
      ret += 20 * incorrect[i] + correctTimes[i];
    }
    return ret;
  }
};

int main() {
  Contestant c[100];
  char w[100];

  // Read cases:
  int idx = 0;
  gets(w);
  int cases = nextInt(w, idx);
  gets(w);

  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    for(int i = 0; i < 100; ++i)
      c[i].reset();
    while(gets(w)) {
      idx = 0;
      int contestant = nextInt(w, idx);
      if(contestant <= 0)
	break;
      --contestant;
      int problem = nextInt(w, idx);
      --problem;
      int time = nextInt(w, idx);
      char L = nextChar(w, idx);
      if(L == 'C')
	c[contestant].addCorrect(problem, time);
      else if(L == 'I')
	c[contestant].addIncorrect(problem);
      else
	c[contestant].addOther();
    }
    // Sort:
    Vec v;
    for(int i = 0; i < 100; ++i) {
      if(!c[i].anySubmissions)
	continue;
      v.push_back(std::tuple<int,int,int>(-c[i].countCorrect(), c[i].penalty(), i));
    }
    std::sort(v.begin(), v.end());

    // Print score board:
    for(Vec::const_iterator it = v.begin(); it != v.end(); ++it) {
      std::cout << (1+std::get<2>(*it)) << " " << -std::get<0>(*it) << " "<< std::get<1>(*it) << std::endl;
    }
    
  }
  return 0;
}
