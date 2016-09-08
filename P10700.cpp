#include <iostream>
#include <stdio.h>

using namespace std;
typedef pair<long long,long long> PP;

PP minmax(int minI, int maxI, int *a, bool *plusses) {
  if(minI+1 == maxI)
    return PP(a[minI], a[minI]);
  long long min = -1;
  long long max = 0;
  for(int splitMax = minI+1; splitMax < maxI; ++splitMax) {
    PP left = minmax(minI, splitMax, a, plusses);
    PP right = minmax(splitMax, maxI, a, plusses);
    if(plusses[splitMax-1]) {
      if(min == -1 || min > left.first+right.first)
	min = left.first+right.first;
      if(max < left.second+right.second)
	max = left.second+right.second;      
    }
    else {
      if(min == -1 || min > left.first*right.first)
	min = left.first*right.first;
      if(max < left.second*right.second)
	max = left.second*right.second;
    }
  }
  return PP(min, max);
}

int main() {
  int T, a[12];
  bool plusses[11];
  string s;
  char c;
  cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    // Parse input:
    cin >> s;
    int size = 1;
    a[0] = 0;
    for(int i = 0; isprint(c = s[i]); ++i) {
      if(c == '+' || c == '*') {
	plusses[size-1] = c == '+';
	a[size] = 0;
	++size;
      }
      else {
	a[size-1] = 10*a[size-1]+c-'0';	
      }
    }
    // Compute min/max:
    PP ret = minmax(0, size, a, plusses);
    cout << "The maximum and minimum are " << ret.second << " and " << ret.first << "." << endl;
  }
  return 0;
}
