#include <iostream>
#include <stdio.h>

using namespace std;

void handleRook(int w, int h) {
  if(w < h)
    cout << w << endl;
  else
    cout << h << endl;  
}

void handleKnight(int w, int h) {
  int ret = ((w+1)/2)*((h+1)/2) + (w/2)*(h/2);
  cout << ret << endl;
}

void handleQueen(int w, int h) {
  if(w < h)
    cout << w << endl;
  else
    cout << h << endl;
}

void handleKing(int w, int h) {
  ++w;
  ++h;
  cout << (w/2)*(h/2) << endl;
}

int main() {
  int cases; cin >> cases;
  for(int cas = 0; cas < cases; ++cas) {
    char unit;
    int w, h;
    cin >> unit >> w >> h;
    switch(unit) {
    case 'r':
      handleRook(w, h);
      break;
    case 'k':
      handleKnight(w, h);
      break;
    case 'Q':
      handleQueen(w, h);
      break;
    case 'K':
      handleKing(w, h);
      break;
    }
  }
  return 0;
}
