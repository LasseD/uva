#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef pair<double,string> DS;

int main() {
  vector<DS> first, other;

  int n;
  double a, b;
  cin >> n;
  string name;

  for(int i = 0; i < n; ++i) {
    cin >> name >> a >> b;
    first.push_back(DS(a,name));
    other.push_back(DS(b,name));
  }

  sort(first.begin(), first.end());
  sort(other.begin(), other.end());

  double best = 9999999;
  string bestNames[4], names[4];

  for(int i = 0; i < 4; ++i) {
    names[0] = first[i].second;
    double total = first[i].first;

    int cnt = 1;
    for(int j = 0; j < n; ++j) {
      if(other[j].second == first[i].second)
	continue; // altready used
      total += other[j].first;
      names[cnt] = other[j].second;
      ++cnt;
      if(cnt == 4)
	break;
    }
    if(total < best) {
      best = total;
      for(int j = 0; j < 4; ++j) {
	bestNames[j] = names[j];
      }
    }
  }

  cout << best << endl;
  for(int i = 0; i <  4; ++i) {
    cout << bestNames[i] << endl;
  }

  return 0;
}
