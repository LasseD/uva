#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  string s;
  while(cin >> s) {
    int hh = 10*(s[0]-'0')+s[1]-'0';
    int mm = 10*(s[2]-'0')+s[3]-'0';
    int ss = 10*(s[4]-'0')+s[5]-'0';
    int cc = 10*(s[6]-'0')+s[7]-'0';
    long time = cc + 100*ss + 100*60*mm + 100*60*60*hh;
    long decitime = time * (10*100*100*100) / (24*60*60*100);
    long decihh = decitime / (100*100*100);
    decitime -= decihh * (100*100*100);
    long decimm = decitime / (100*100);
    decitime -= decimm * (100*100);
    long deciss = decitime / (100);
    decitime -= deciss * (100);
    long decicc = decitime;
    printf("%0.1ld%0.2ld%0.2ld%0.2ld\n", decihh, decimm, deciss, decicc);
  }
  return 0;
}
