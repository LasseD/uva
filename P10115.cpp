#include <iostream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

typedef pair<string,string> PP;
typedef vector<PP> Vector;

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return ret;
}

int main() {
  char line[300];
  while(true) {
    int rules = readUInt();
    if(rules == 0)
      return 0;
    Vector v;
    for(int i = 0; i < rules; ++i) {
      gets(line);
      string s1(line);
      gets(line);
      string s2(line);
      v.push_back(PP(s1,s2));
    }
    gets(line);
    string s(line);
    // Handle line:
    for(unsigned int ruleI = 0; ruleI < v.size(); ++ruleI) {
      string from = v[ruleI].first, to = v[ruleI].second;
      int start = 0;
      while((start = s.find(from, start)) != (int)string::npos) {
        s.replace(start, from.length(), to);
        start -= from.length()+1;
	if(start < 0)
	  start = 0;
      }
    }
    cout << s << endl;
  }
}
