#include <iostream>
#include <stdio.h>

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
  //bool mtx[100*100];
  int N, M, e, upRays[100];

  while(true) {
    std::cin >> N >> M;
    if(N == 0 && M == 0)
      return 0;
    for(int x = 0; x < M; ++x) {
      upRays[x] = 0;
    }

    int area = 0;

    for(int y = 0; y < N; ++y) {
      for(int x = 0; x < M; ++x) {
	std::cin >> e;
	if(e == 1)
	  upRays[x] = 0;
	else
	  ++upRays[x];
      }
      for(int x = 0; x < M; ++x) {
	int upRay = upRays[x];
	if(upRay > 0) {
	  int xMin = x, xMax = x;
	  while(xMin > 0 && upRays[xMin-1]>=upRay)
	    --xMin;
	  while(xMax < M-1 && upRays[xMax+1]>=upRay)
	    ++xMax;
	  int newArea = upRay*(xMax-xMin+1);
	  if(area < newArea)
	    area = newArea;
	}
      }
    }
    std::cout << area << std::endl;
  }
}
