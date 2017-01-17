#include <iostream>
#include <set>

using namespace std;

typedef pair<int,int> PP;

int main() {
  int n, b, x; // number of days.
  while(true) {
    cin >> n;
    if(n == 0)
      return 0;

    int g = 0; // to make elements unique.
    set<PP> bills;

    long long ret = 0;
    for(int day = 0; day < n; ++day) {
      // Add new bills:
      cin >> b;
      for(int i = 0; i < b; ++i) {
	cin >> x;
	bills.insert(PP(x, g++));
      }
      PP minBill = *bills.begin();
      PP maxBill = *bills.rbegin();
      bills.erase(minBill);
      bills.erase(maxBill);
      //cerr << (maxBill.first-minBill.first) << endl;
      ret += maxBill.first-minBill.first;
    }
    cout << ret << endl;
  } // while true main loop
} // main
