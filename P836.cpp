#include <iostream>
#include <stdio.h>
#include <cstring>

/*
Process lines while maintaining length of up-rays:

Example:
Maze   Up-rays Max areas
XX-XX  00100   00100
XX--X  00210   00220
----X  11320   12340
XX-XX  00400   00400

=> O(n^3)
 */
int main () {
  int cases = 0, upRays[25];
  char c, w[39];
  gets(w);//scanf("%d", &cases); getchar();
  for(int i = 0; isdigit(w[i]); ++i)
    cases = 10 * cases + w[i] - '0';
  //std::cerr << "Cases: " << cases << std::endl;

  for(int cas = 0; cas < cases; ++cas) {
    gets(w);
    int N = 1;
    memset(upRays, 0, 25*sizeof(int));
    int area = 0;

    for(int y = 0; y < N; ++y) {
      gets(w);
      for(int x = 0; isdigit(c = w[x]); ++x) {
	if(y == 0 && x >= N)
	  N = x+1;
	if(c == '1')
	  ++upRays[x];
	else
	  upRays[x] = 0;
      }
      //std::cerr << "N=" << N << ", W=" << w << std::endl;
      for(int x = 0; x < N; ++x) {
	int upRay = upRays[x];
	if(upRay > 0) {
	  int xMin = x, xMax = x;
	  while(xMin > 0 && upRays[xMin-1]>=upRay)
	    --xMin;
	  while(xMax < N-1 && upRays[xMax+1]>=upRay)
	    ++xMax;
	  int newArea = upRay*(xMax-xMin+1);
	  if(area < newArea)
	    area = newArea;
	}
      }
    } // for y
    if(cas > 0)
      std::cout << std::endl;
    std::cout << area << std::endl;
  } // for cas
  return 0;
}
