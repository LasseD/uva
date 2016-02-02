#include <iostream>
#include <stdio.h>
#include <stack>

int bestUsage(int sizeVals, int *vals, int max, std::stack<int> &s) {
  int *b = new int[(max+1)*(sizeVals+1)]; // index (max+1)*(valsI+1)+sum : Best after considering vals[valsI] for value val
  for(int i = 0; i < (max+1)*(sizeVals+1); ++i)
    b[i] = 0;
  
  for(int valsI = 0; valsI < sizeVals; ++valsI) { // For all vals
    int val = vals[valsI]; // Can I improve b using val?:
    for(int i = 0; i <= max; ++i)
      b[(max+1)*(valsI+1)+i] = b[(max+1)*valsI+i];

    for(int i = max; i >= val; --i) {
      int bi = (max+1)*(valsI+1)+i;
      int biPrev = (max+1)*valsI+i-val;
      int v = val + b[biPrev]; // New value of b when using val
      if(v > b[bi])
	b[bi] = v;
    }
  }
  /*
  for(int sum = 0; sum <= max; ++sum) {
    for(int j = 0; j <= sizeVals; ++j) {
      printf("%2d ", b[(max+1)*(j)+sum]);
    }
    printf("\n");
  }//*/

  int sum = max;
  int valsI = sizeVals-1;
  while(valsI >= 0 && sum > 0) {
    if(b[(max+1)*(valsI+1)+sum] != b[(max+1)*valsI+sum]) {
      sum -= vals[valsI];
      s.push(vals[valsI--]);
    }
    else
      --valsI;
  }

  int ret = b[(max+1)*(sizeVals+1)-1];
  delete[] b;
  return ret;
}

int main() {
  int N, numTracks, a[20];
  while(std::cin >> N >> numTracks) {
    for(int i = 0; i < numTracks; ++i)
      std::cin >> a[i];
    //std::sort(a, a+m);
    std::stack<int> s;
    int sum = bestUsage(numTracks, a, N, s);
    while(!s.empty()) {
      std::cout << s.top() << " ";
      s.pop();
    }
    //std::cerr << "Sum: " << sum << ", half usage: " << maxHalf << std::endl;
    std::cout << "sum:" << sum << std::endl;
  }
}
