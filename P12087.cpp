#include <iostream>
#include <stdio.h>

long get(int x, int y, long *querySumDown, long *querySumUp, long *querySumLeft, long *querySumRight) {
  //std::cerr << "(" << x << "," << y << ")=" << querySumDown[y+1] <<"+"<< querySumUp[y-1] <<"+"<< querySumLeft[x-1] <<"+"<< querySumRight[x+1] << "=" << (querySumDown[y+1] + querySumUp[y-1] + querySumLeft[x-1] + querySumRight[x+1]) << std::endl;
  return querySumDown[y+1] + querySumUp[y-1] + querySumLeft[x-1] + querySumRight[x+1];
}

int readInt(char *w, int &idx) {
  while(!isdigit(w[idx]))
    ++idx;
  int ret = 0;
  while(isdigit(w[idx])) {
    ret = ret * 10 + (w[idx]-'0');      
    ++idx;
  }
  return ret;
}

void writeInt(long n, char *w, int &idx) {
  int len = 1;
  long copy = n;
  while(copy > 9) {
    ++len;
    copy/=10;
  }
  for(int i = 0; i < len; ++i) {
    //std::cerr << (char)('0'+(n%10)) << std::endl;
    w[idx+len-i-1] = '0'+(n%10);
    n/=10;
  }
  idx+=len;
}

int main() {
  char w[501*5];

  int rowSums[502*502]; // (y+1)*(c+1) + x+1
  int colSums[502*502];
  long querySumRight[502];
  long querySumUp[502];
  long querySumLeft[502];
  long querySumDown[502];

  int T, r, c, q, val, x1, x2, y1, y2;
  gets(w);
  int idx = 0;
  T = readInt(w, idx);
  char testCaseStr[13] = "Test Case X:";
  char outStr[39];
  for(int cas = 1; cas <= T; ++cas) {
    //printf("Test Case %d:\n", cas);
    testCaseStr[10] = '0'+cas;
    puts(testCaseStr);
    gets(w); idx = 0;
    r = readInt(w, idx);
    c = readInt(w, idx);
    q = readInt(w, idx);
    int C = c+1;
    //int R = r+1;
    for(int y = 0; y <= r; ++y)
      rowSums[y*C] = colSums[y*C] = 0;
    for(int x = 0; x <= c; ++x)
      rowSums[x] = colSums[x] = 0;

    // Read matrix:
    for(int y = 1; y <= r; ++y) {
      gets(w); idx = 0;      
      for(int x = 1; x <= c; ++x) {
	val = readInt(w, idx);
	rowSums[y*C+x] = val + rowSums[y*C+x-1];
	colSums[y*C+x] = val + colSums[(y-1)*C+x];
      }
    }
    /*
    // Debugging:
    for(int y = 0; y <= r; ++y) {
      for(int x = 0; x <= c; ++x) {
	std::cerr << rowSums[y*C+x] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << std::endl;
    for(int y = 0; y <= r; ++y) {
      for(int x = 0; x <= c; ++x) {
	std::cerr << colSums[y*C+x] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << std::endl;//*/
    
    // Process queries:
    for(int i = 1; i <= q; ++i) {
      gets(w); idx = 0;      
      y1 = readInt(w, idx);
      x1 = readInt(w, idx);
      y2 = readInt(w, idx);
      x2 = readInt(w, idx);
      if(x1 > x2)
	std::swap(x1, x2);
      if(y1 > y2)
	std::swap(y1, y2);
      // Preprocess querySums:
      long pop = 0;
      querySumLeft[x1-1] = 0;
      for(int xx = x1; xx <= x2; ++xx) {
	long add = colSums[y2*C+xx]-colSums[(y1-1)*C+xx];
	pop += add;
	querySumLeft[xx] = querySumLeft[xx-1] + pop;
	//std::cerr << "Left " << xx << ": " << querySumLeft[xx] << std::endl;
      }
      pop = 0;
      querySumUp[y1-1] = 0;
      for(int yy = y1; yy <= y2; ++yy) {
	long add = rowSums[yy*C+x2]-rowSums[yy*C+x1-1];	
	pop += add;
	querySumUp[yy] = querySumUp[yy-1] + pop;
	//std::cerr << "Up " << yy << ": " << querySumUp[yy] << std::endl;
      }
      pop = 0;
      querySumRight[x2+1] = 0;
      for(int xx = x2; xx >= x1; --xx) {
	long add = colSums[y2*C+xx]-colSums[(y1-1)*C+xx];
	pop += add;
	querySumRight[xx] = querySumRight[xx+1] + pop;
	//std::cerr << "Right " << xx << ": " << querySumRight[xx] << std::endl;
      }
      pop = 0;
      querySumDown[y2+1] = 0;
      for(int yy = y2; yy >= y1; --yy) {
	long add = rowSums[yy*C+x2]-rowSums[yy*C+x1-1];
	pop += add;
	querySumDown[yy] = querySumDown[yy+1] + pop;
	//std::cerr << "Down " << yy << ": " << querySumDown[yy] << std::endl;
      }
	
      // Walk to best in grid:
      int bestX = x1;
      int bestY = y1;
      long best = get(x1, y1, querySumDown, querySumUp, querySumLeft, querySumRight);
      bool improved = true;
      while(improved) {
	improved = false;
	if(bestY < y2) {
	  long candidate = get(bestX, bestY+1, querySumDown, querySumUp, querySumLeft, querySumRight);
	  if(candidate < best) {
	    ++bestY;
	    best = candidate;
	    improved = true;
	    continue;
	  }
	}
	if(bestX < x2) {
	  long candidate = get(bestX+1, bestY, querySumDown, querySumUp, querySumLeft, querySumRight);
	  if(candidate < best) {
	    ++bestX;
	    best = candidate;
	    improved = true;
	  }
	}	
      }
      idx = 0;      
      writeInt(i, outStr, idx);
      outStr[idx++] = ' ';
      writeInt(best, outStr, idx);
      outStr[idx++] = '\0';
      puts(outStr);
      //printf("%d %li\n", i, best);//std::cout << i << " " << best << std::endl;
    }

    puts("");
  }
}
