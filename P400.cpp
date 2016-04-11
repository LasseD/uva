#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

typedef std::vector<std::string> Vector;

void printSpaces(int n) {
  for(int i = 0; i < n; ++i)
    printf(" ");
}

int main() {
  int N;
  std::string s;
  while(std::cin >> N) {
    printf("------------------------------------------------------------\n");
    Vector v;
    unsigned int maxLength = 1;
    for(int i = 0; i < N; ++i) {
      std::cin >> s;
      if(s.size() > maxLength)
	maxLength = s.size();
      v.push_back(s);
    }
    std::sort(v.begin(), v.end());
    int columns = (60-maxLength)/(maxLength+2)+1; // (C - 1) * (L + 2) + L <= 60
    int rows = (N+columns-1)/columns;
    for(int row = 0; row < rows; ++row) {
      for(int column = 0; column < columns; ++column) {
	int idx = rows*column+row;
	if(idx >= N)
	  break;
	if(column > 0)
	  printSpaces(2+maxLength-v[rows*(column-1)+row].size());
	printf("%s", v[idx].c_str());
      } // for columns
      printf("\n");
    } // for rows
  } // while N
}
