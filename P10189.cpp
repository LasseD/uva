#include <iostream>
#include <ctype.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))

bool readInts(int &a, int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  char w[20];
  std::cin.getline(w, 20);
  for(int i = 0; i < 20; ++i) {
    if(w[i] == '-') {
      if(!aStarted) {
	aStarted = true;
      }
    }      
    else if(w[i] >= '0' && w[i] <= '9') {
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
  return a != 0 || b != 0;
}

#define LEN 109

int main() {
  int N, M;
  char line[LEN];
  bool F[10000];
  bool first = true;
  for(int field = 0; readInts(N, M); ++field) {
    if(!first)
      std::cout << std::endl;
    first = false;
    std::cout << "Field #" << (field+1) << ":" << std::endl;

    for(int i = 0; i < N; ++i) {
      std::cin.getline(line, LEN);
      for(int j = 0; j < M; ++j) {
	F[i*M+j] = (line[j] == '*');
      }
    }
    //std::cerr << N << "x" << M << std::endl;

    for(int i = 0; i < N; ++i) {
      for(int j = 0; j < M; ++j) {
	if(F[i*M+j]) {
	  std::cout << "*";
	  continue;
	}
	int bombs = 0;
	for(int x = MAX(0, j-1); x <= MIN(j+1, M-1); ++x) {
	  for(int y = MAX(0, i-1); y <= MIN(i+1, N-1); ++y) {
	    if(F[y*M+x])
	      ++bombs;
	  }	  
	}
	std::cout << bombs;
      }
      std::cout << std::endl;
    }
    
  }
  return 0;
}
