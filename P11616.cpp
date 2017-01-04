#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void toRomanUpToTen(char *w, int &idx, int n) {
  if(n <= 3) {
    for(int i = 0; i < n; ++i)
      w[idx++] = 'I';
    return;
  }
  if(n == 4) {
    w[idx++] = 'I';
    w[idx++] = 'V';
    return;
  }
  if(n <= 8) {
    w[idx++] = 'V';
    for(int i = 6; i <= n; ++i)
      w[idx++] = 'I';
    return;
  }
  if(n == 9) {
    w[idx++] = 'I';
  }
  w[idx++] = 'X';
}

void toRomanTens(char *w, int &idx, int n) {
  if(n <= 3) {
    for(int i = 0; i < n; ++i)
      w[idx++] = 'X';
    return;
  }
  if(n == 4) {
    w[idx++] = 'X';
    w[idx++] = 'L';
    return;
  }
  if(n <= 8) {
    w[idx++] = 'L';
    for(int i = 6; i <= n; ++i)
      w[idx++] = 'X';
    return;
  }
  if(n == 9) {
    w[idx++] = 'X';
  }
  w[idx++] = 'C';
}

void toRomanHundreds(char *w, int &idx, int n) {
  if(n <= 3) {
    for(int i = 0; i < n; ++i)
      w[idx++] = 'C';
    return;
  }
  if(n == 4) {
    w[idx++] = 'C';
    w[idx++] = 'D';
    return;
  }
  if(n <= 8) {
    w[idx++] = 'D';
    for(int i = 6; i <= n; ++i)
      w[idx++] = 'C';
    return;
  }
  if(n == 9) {
    w[idx++] = 'C';
  }
  w[idx++] = 'M';
}

void toRomanThousands(char *w, int &idx, int n) {
  for(int i = 0; i < n; ++i)
    w[idx++] = 'M';
}

void toRoman(char *w, unsigned int n) {
  int idx = 0;
  toRomanThousands(w, idx, n/1000);
  //w[idx++] = '_';
  toRomanHundreds(w, idx, n/100 % 10);
  //w[idx++] = '_';
  toRomanTens(w, idx, n/10 % 10);
  //w[idx++] = '_';
  toRomanUpToTen(w, idx, n%10);
  w[idx] = '\0';
}

int romanToDecimal(char r) {
  switch(r) {
  case 'I':
    return 1;
  case 'V':
    return 5;
  case 'X':
    return 10;
  case 'L':
    return 50;
  case 'C':
    return 100;
  case 'D':
    return 500;
  case 'M':
    return 1000;
  default: return 0;
  }
}

int romanToDecimal(char const * const r) {
  int ret = 0;
  char c;
  for(int i = 0; isalpha(c = r[i]); ++i) {
    int add = romanToDecimal(c);
    if(romanToDecimal(r[i+1]) > add)
      ret -= add;
    else
      ret += add;
  }
  return ret;
}

int main() {
  char roman[20];

  char s[20];
  while(scanf("%s", s) == 1) {
    if(isdigit(s[0])) {
      // To roman:
      toRoman(roman, atoi(s));
      cout << roman << endl;
    }
    else {
      cout << romanToDecimal(s) << endl;
    }
  }
  return 0;
}
