#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

struct Array {
  int D;
  ll B, Ld[11], Ud[11], Cd[11];
};

int main() {
  // Read input:
  int N, R; // N = |arrays|, R = |queries|
  cin >> N >> R;
  map< string, Array* > m;
  for(int i = 0; i < N; ++i) {
    string name;
    Array *a = new Array();
    ll CD;
    cin >> name >> a->B >> CD >> a->D;
    for(int j = 1; j <= a->D; ++j)
      cin >> a->Ld[j] >> a->Ud[j];
    // Compute Cd's:
    a->Cd[a->D] = CD;
    for(int d = a->D-1; d >= 1; --d) {
      a->Cd[d] = a->Cd[d+1] * (a->Ud[d+1] - a->Ld[d+1] + 1);
    }
    a->Cd[0] = a->B;
    for(int d = 1; d <= a->D; ++d) {
      a->Cd[0] -= a->Cd[d] * a->Ld[d];
    }
    // Insert into map:
    m.insert(make_pair(name, a));
  }
  // Handle queries:
  for(int i = 0; i < R; ++i) {
    string arrayName;
    cin >> arrayName;
    Array *a = m[arrayName];
    ll dims[10];
    for(int j = 0; j < a->D; ++j)
      cin >> dims[j];
    cout << arrayName << "[" << dims[0];
    for(int j = 1; j < a->D; ++j)
      cout << ", " << dims[j];
    cout << "] = ";
    
    ll position = a->Cd[0];
    for(int j = 1; j <= a->D; ++j)
      position += a->Cd[j] * dims[j-1];
    cout << position << endl;
  }
}
