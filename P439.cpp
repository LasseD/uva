#include <iostream>
#include <stdio.h>

int main() {
  // init variables:
  const int nx[8] = {-2, -2, -1, -1, 1,  1, 2,  2};
  const int ny[8] = {-1,  1, -2,  2, 2, -2, 1, -1};

  int best[64*64];
  for(int i = 0; i < 64*64; ++i)
    best[i] = 100;
  for(int i = 0; i < 64; ++i)
    best[64*i+i] = 0;

  // Build solutions:
  bool improved = true;
  while(improved) {
    improved = false;
    for(int x1 = 0; x1 < 8; ++x1) {
      for(int y1 = 0; y1 < 8; ++y1) {
	for(int x2 = 0; x2 < 8; ++x2) {
	  for(int y2 = 0; y2 < 8; ++y2) {
	    int min = best[64*(8*x1+y1) + 8*x2+y2];
	    for(int i = 0; i < 8; ++i) {
	      int x3 = x2 + nx[i];
	      if(x3 < 0 || x3 >= 8) {
		continue;
	      }
	      int y3 = y2 + ny[i];
	      if(y3 < 0 || y3 >= 8) {
	        continue;
	      }
	      if(1 + best[64*(8*x1+y1) + 8*x3+y3] < min) {
		min = 1 + best[64*(8*x1+y1) + 8*x3+y3];
		improved = true;
	      }
	    } // i
	    best[64*(8*x1+y1) + 8*x2+y2] = min;
	  } // y2
	} // x2
      } // y1
    } // x1
  } // improved

  // Run i/o:
  char line[7];
  while(std::cin.getline(line, 7)) {
    int x1, y1, x2, y2;
    line[2] = line[5] = '\0';
    x1 = (int)(line[0]-'a');
    x2 = (int)(line[3]-'a');
    y1 = (int)(line[1]-'1');
    y2 = (int)(line[4]-'1');
    int n = best[64*(8*x1+y1) + 8*x2+y2];
    std::cout << "To get from " << line << " to " << &line[3] << " takes " << n << " knight moves." << std::endl;
  }
  return 0;
}
