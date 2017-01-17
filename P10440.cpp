#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int,int> PP;

int main() {
  int cases, a[1500], b[1500]; // b is preferred departure times.
  cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    int n, t, m; // capacity n, t time, m cars
    cin >> n >> t >> m;
    for(int i = 0; i < m; ++i) {
      cin >> a[i];
      a[i] = -a[i];
    }
    sort(a, a+m);
    int bI = 0;
    for(int i = 0; i < m; i += n) {
      b[bI++] = -a[i];
    }
    sort(b, b+bI); // I'm lazy.
    int lastDepartureTime = b[0]; // first ferry trip.
    for(int i = 1; i < bI; ++i) {
      if(lastDepartureTime + 2*t > b[i])
	lastDepartureTime += 2*t;
      else
	lastDepartureTime = b[i];
    }
    cout << (lastDepartureTime+t) << " " << bI << endl;
  } // for cas
  return 0;
} // main

