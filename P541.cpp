#include <iostream>

int main() {
  bool M[10000];
  int N;
  while(true) {
    std::cin >> N;
    if(N == 0)
      return 0;
    int corruptedRows = 0;
    int corruptedColumns = 0;
    int lastCorruptedRow = -1;
    int lastCorruptedColumn = -1;
    for(int y = 0; y < N; ++y) {
      bool even = true;
      for(int x = 0; x < N; ++x) {
	int bit;
	std::cin >> bit;
	M[y*N+x] = bit == 1;
	if(M[y*N+x])
	  even = !even;
      }
      if(!even) {
	++corruptedRows;
	lastCorruptedRow = y;
      }
    }
    for(int x = 0; x < N; ++x) {
      bool even = true;
      for(int y = 0; y < N; ++y) {
	if(M[y*N+x])
	  even = !even;
      }
      if(!even) {
	++corruptedColumns;
	lastCorruptedColumn = x;
      }      
    }
    if(corruptedRows == 0 && corruptedColumns == 0)
      std::cout << "OK" << std::endl;
    else if(corruptedRows == 1 && corruptedColumns == 1)
      std::cout << "Change bit (" << (lastCorruptedRow+1) << "," << (lastCorruptedColumn+1) << ")" << std::endl;
    else
      std::cout << "Corrupt" << std::endl;
  }
}
