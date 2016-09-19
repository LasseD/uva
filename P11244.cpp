#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
  char prevprev[109], prev[109], curr[109];
  int width, height;
  while(true) {
    scanf("%d %d\n", &height, &width);
    if(width == 0 && height == 0)
      return 0;

    memset(prev, '.', width*sizeof(char));
    gets(curr);
    long stars = 0;
    for(int y = 0; y < height; ++y) {
      swap(prevprev, prev);
      swap(prev, curr);
      if(y < height-1)
	gets(curr);
      else
	memset(curr, '.', width*sizeof(char));

      // Sum for prev:
      for(int x = 0; x < width; ++x) {
	if(prev[x] != '*')
	  continue;
	bool ok = true;
	if((x > 0 && prevprev[x-1] == '*') || prevprev[x] == '*' || (x < width-1 && prevprev[x+1] == '*') ||
           (x > 0 && prev[x-1] == '*') || (x < width-1 && prev[x+1] == '*') ||
           (x > 0 && curr[x-1] == '*') || curr[x] == '*' || (x < width-1 && curr[x+1] == '*'))
	  ok = false;
	if(ok)
	  ++stars;
      } // for x
    } // for y
    cout << stars << endl;
  } // while true
} // int main
