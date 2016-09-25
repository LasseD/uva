#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
  string s;
  while(cin >> s) {
    int expect = 1;
    bool ok = true;
    for(unsigned int i = 0; ok && i < s.size(); ++i) {
      char c = s[i];
      if(c >= 'p' && c <= 'z') {
	--expect;
	if(expect < 0)
	  ok = false;
      }
      else if(c == 'N') {
	if(expect <= 0)
	  ok = false;
      }
      else {
	if(expect <= 0)
	  ok = false;
	++expect;      
      }
    }
    if(expect != 0)
      ok = false;
    if(ok)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}
