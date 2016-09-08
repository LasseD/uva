#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int T, hh, mm;
  string s;
  cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    cin >> s;
    hh = 10*(s[0]-'0')+s[1]-'0';
    mm = 10*(s[3]-'0')+s[4]-'0';
    if(mm != 0)
      mm = 60-mm;
    // 12:XX -> 11:XX, 5:XX -> 6:XX, 6:XX -> 5:XX, 4:XX -> 7:XX
    if(hh == 12) {
      if(mm != 0)
	hh = 11;
    }
    else if(hh == 11 && mm != 0)
      hh = 12;
    else {
      if(mm != 0)
	hh = 11-hh;
      else
	hh = 12-hh;
    }
    printf("%02d:%02d\n", hh, mm);
  }
  return 0;
}
