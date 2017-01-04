#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef pair<double,double> EventPoint; // x, multiplier

int main() {
  double rm;

  int cases; cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      cout << endl;
    int size;
    cin >> size;
    EventPoint *events = new EventPoint[2*size];
    for(int i = 0; i < 2*size; i+=2) {
      cin >> events[i].first >> rm >> events[i+1].first >> rm >> events[i].second;
      events[i+1].second = 1/events[i].second;
      if(events[i].first > events[i+1].first)
	swap(events[i].first, events[i+1].first);
    }
    sort(events, events+2*size);
    
    printf("%d\n", 2*size+1);
    printf("-inf %.3lf 1.000\n", events[0].first);
    double d = events[0].second;
    for(int i = 1; i < 2*size; ++i) {
      printf("%.3lf %.3lf %.3lf\n", events[i-1].first, events[i].first, d);
      d *= events[i].second;
    }
    printf("%.3lf +inf 1.000\n", events[2*size-1].first);
    delete[] events;
  }
  return 0;
}
