#include<iostream>
#include<vector>
#include<algorithm>
#include <set>

using namespace std;

#define MAX(a,b) ((a) < (b) ? (b) : (a))

typedef long long LL;
typedef pair<int,int> PI;
typedef pair<int,PI> PII;

int main() {
  int b, n, e;
  cin >> b >> n >> e;
  int speeds[3];
  for(int i = 0; i < 3; ++i) {
    cin >> speeds[i];
  }
  int k = (b+n+e)/2;
  vector<int> c(k);
  for(int i = 0; i < k; ++i)
    cin >> c[i];

  int lower = c[0]*b*2;
  int upper = c[0]*e*2;
  while(lower < upper) {
    int mid = (lower+upper)/2;

    bool ok = true;
    int remainE = e;
    int remainN = n;
    int remainB = b;
    for(int i = 0; i < k; ++i) {
      if(remainB >= 2) {
	if(c[i]*2*speedB >= mid) {
	  ok = true;
	  break;
	}
	if(remainN > 0) {
	  if(c[i]*(speedB

	}
      }
    }
    // TODO Try mid;
  }
}
