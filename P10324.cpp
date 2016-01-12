#include <iostream>
#include <stdio.h>

void readInt(unsigned int &a) {
  a = 0;
  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      a = a*10 + (w[i]-'0');
    }
    else if(!isprint(w[i])) {
      break;
    }
  }
}

void readInts(unsigned int &a, unsigned int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
      if(aDone)
	b = b*10 + (w[i]-'0');
      else {
	a = a*10 + (w[i]-'0');
	aStarted = true;
      }
    }
    else {
      if(!isprint(w[i]))
	break;
      if(aStarted)
	aDone = true;
    }
  }
}

int lowerBound(unsigned int I, unsigned int const * const a, unsigned int sizeA) {
  if(sizeA == 0 || I < a[0])
    return -1;
  unsigned int low = 0;
  unsigned int high = sizeA;
  while(low < high-1) {
    unsigned int mid = (low+high)/2;
    if(a[mid] < I) {
      low = mid;
    }
    else if(a[mid] == I) {
      return mid;
    }
    else { // a[mid] > I
      high = mid;
    }
  }
  return (int)low;
}

int main() {
  char *line = new char[1000001];
  unsigned int *shifts = new unsigned int[1000000];
  unsigned int n, I, J;
  for(int cas = 1; gets(line) && isprint(line[0]); ++cas) {
    unsigned int numShifts = 0;
    std::cout << "Case " << cas << ":" << std::endl;
    unsigned int size = 1;
    for(; isprint(line[size]); ++size) {
      if(line[size] != line[size-1]) {
	shifts[numShifts++] = size;
      }
    }
    shifts[numShifts] = 1000001;
    /*std::cerr << "Shifts: ";
    for(unsigned int i = 0; i < numShifts; ++i)
      std::cerr << shifts[i] << ",";
    std::cerr << std::endl;//*/

    readInt(n);
    for(unsigned int i = 0; i < n; ++i) {
      readInts(I, J);
      if(I > J)
	std::swap(I, J);
      if(numShifts == 0) {
	std::cout << "Yes" << std::endl;
	continue;
      }
      int lowerI = lowerBound(I, shifts, numShifts);
      //std::cerr << "Lower I (" << I << "," << J << "): " << lowerI << std::endl;
      if(lowerI == -1) {
	if(shifts[0] <= J)
	  std::cout << "No" << std::endl;
	else
	  std::cout << "Yes" << std::endl;	  
	continue;
      }
      if(lowerI == (int)numShifts-1) {
	std::cout << "Yes" << std::endl;	  
	continue;
      }

      if(shifts[lowerI+1] <= J)
	std::cout << "No" << std::endl;
      else
	std::cout << "Yes" << std::endl;
    }
  }
  delete[] line;
  delete[] shifts;
  return 0;
}
