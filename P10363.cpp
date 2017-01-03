#include <iostream>
#include <cstdio>

using namespace std;

int count(string &s1, string &s2, string &s3, char color) {
  int ret = 0;
  for(int i = 0; i < 3; ++i) {
    if(s1[i] == color) ++ret;
    if(s2[i] == color) ++ret;
    if(s3[i] == color) ++ret;
  }
  cerr << "Count " << color << ": " << ret << endl;
  return ret;
}

bool wins(string &s1, string &s2, string &s3, char color) {
  if(s1[0] == color && s2[1] == color && s3[2] == color)
    return true;
  if(s3[0] == color && s2[1] == color && s1[2] == color)
    return true;

  if(s1[0] == color && s1[1] == color && s1[2] == color)
    return true;
  if(s2[0] == color && s2[1] == color && s2[2] == color)
    return true;
  if(s3[0] == color && s3[1] == color && s3[2] == color)
    return true;  

  for(int i = 0; i < 3; ++i) {
    if(s1[i] == color && s2[i] == color && s3[i] == color)
      return true;    
  }

  return false;
} 

bool ok(bool winX, bool winO, int countX, int countO) {
  if(winX) {
    if(winO)
      return false;
    return countX-1 == countO;
  }
  else if(winO) {
    return countX == countO;
  }
  else {
    // No win: Check counts:
    return countX == countO || countX-1 == countO;
  }
}

int main() {
  int cases;
  string s1, s2, s3;
  cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    cin >> s1 >> s2 >> s3;
    cerr << s1 << endl << s2 << endl << s3 << endl;
    int countX = count(s1, s2, s3, 'X');
    int countO = count(s1, s2, s3, 'O');
    bool winX = wins(s1, s2, s3, 'X');
    bool winO = wins(s1, s2, s3, 'O');
    cerr << "Wins X: " << winX << ", Win O: " << winO << endl;

    bool isOK = ok(winX, winO, countX, countO);
    if(isOK)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
  return 0;
}
