#include <iostream>
#include <stdio.h>
#include <sstream>
#include <algorithm>

typedef std::pair<int,int> Interval;
typedef std::string String;
typedef std::stringstream SS;

int timeToMinutes(const String &s) {
  int ret = 0;
  ret += 10*60*(s[0]-'1');
  ret += 60*(s[1]-'0');
  ret += 10*(s[3]-'0');
  ret += (s[4]-'0');
  //std::cerr << s << " -> " << ret << std::endl;
  return ret;
}

int main() {
  String line, from, to;
  int N;

  for(int cas = 1; std::getline(std::cin,line); ++cas) {
    std::stringstream ss1; ss1 << line; ss1 >> N;
    Interval *appointments = new Interval[N+1];
    //std::cerr << "Intervals=" << N << std::endl;

    for(int i = 0; i < N; ++i) {
      std::stringstream ss2;
      std::getline(std::cin,line); ss2 << line; ss2 >> from >> to;
      appointments[i] = Interval(timeToMinutes(from), timeToMinutes(to));
    }
    std::sort(appointments, appointments+N);
    appointments[N] = Interval(8*60, 100*60);
    
    int best = appointments[0].first;
    int bestStart = 0;    
    for(int i = 1; i < N+1; ++i) {
      if(appointments[i].first - appointments[i-1].second > best) {
	best = appointments[i].first - appointments[i-1].second;
	bestStart = appointments[i-1].second;
      }
    }

    delete[] appointments;
    if(best >= 60)
      printf("Day #%d: the longest nap starts at 1%d:%.2d and will last for %d hours and %d minutes.\n", cas, bestStart/60, bestStart%60, best/60, best%60);
    else
      printf("Day #%d: the longest nap starts at 1%d:%.2d and will last for %d minutes.\n", cas, bestStart/60, bestStart%60, best);
  }  
  return 0;
}
