#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
typedef vector<string> Vec;

int main() {
  string song[] = {"Happy", "birthday", "to", "you",
                   "Happy", "birthday", "to", "you",
		   "Happy", "birthday", "to", "Rujia",
		   "Happy", "birthday", "to", "you",};
  string s;
  int n;
  cin >> n;
  Vec v(n);
  for(int i = 0; i < n; ++i)
    cin >> v[i];
  
  int j = 0;
  while(j < n) {
    // sing!
    for(int i = 0; i < 16; ++i) {
      cout << v[j%n] << ": " << song[i] << endl;
      ++j;
    }
  }
  return 0;
}
