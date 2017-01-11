#include <iostream>
#include <cstdio>

using namespace std;

int mass(char c) {
  switch(c) {
  case 'C':
    return 12010;
  case 'H':
    return  1008;
  case 'O':
    return 16000;
  case 'N':
    return 14010;
  default:
    return 0;
  }
}

int main() {
  int T;
  cin >> T;
  for(int cas = 0; cas < T; ++cas) {
    string s;
    cin >> s;
    int sum = 0;
    char prev = 'X';
    int mult = 0;
    for(unsigned int j = 0; j < s.size(); ++j) {
      char c = s[j];
      if(isdigit(c)) {
	mult = 10*mult + (c-'0');
      }
      else {
	if(mult == 0)
	  mult = 1;
	sum += mass(prev)*mult;
	prev = c;
	mult = 0;
      }
    }
    // Handle last element:
    if(mult == 0)
      mult = 1;
    sum += mass(prev)*mult;
    
    printf("%d.%0.3d\n", sum/1000, sum%1000);
  }
  return 0;
}
