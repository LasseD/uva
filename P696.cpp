#include <iostream>
#include <stdio.h>

using namespace std;

void handleKnight(int w, int h) {
  int ret = ((w+1)/2)*((h+1)/2) + (w/2)*(h/2);
  if(w == 1)
    ret = h;
  else if(h == 1)
    ret = w;
  else if(w == 2) {
    switch(h%4) {
    case 0:
      ret = 4*(h/4);
      break;
    case 1:
      ret = 4*(h/4)+2;
      break;
    case 2:
    case 3:
      ret = 4*(h/4)+4;
      break;
    }
  }
  else if(h == 2) {
    switch(w%4) {
    case 0:
      ret = 4*(w/4);
      break;
    case 1:
      ret = 4*(w/4)+2;
      break;
    case 2:
    case 3:
      ret = 4*(w/4)+4;
      break;
    }
  }
  cout << ret << " knights may be placed on a " << w << " row " << h << " column board." << endl;
}

int main() {
  int w, h;
  while(true) {
    cin >> w >> h;
    if(w == 0 && h == 0)
      return 0;
    handleKnight(w, h);
  }
}
