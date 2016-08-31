#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>

#define LINE_LENGTH 1008

#define MAX(a,b) ((a) < (b) ? (b) : (a))

int longestSubSequence(char const * const s1, char const * const s2, int len) {
  if(len == 0)
    return 0;
  int *a = new int[2*(len+1)]; // +1 for empty first character.
  int prevColumn = 0;
  for(int i = 0; i <= len; ++i)
    a[i] = 0;
  for(int s2I = 0; s2I < len; ++s2I) {
    int startI = (1-prevColumn)*(len+1);
    int startPrevI = prevColumn*(len+1);
    a[startI] = 0; // empty first character.
    for(int s1I = 0; s1I < len; ++s1I) {
      if(s1[s1I] == s2[s2I]) {
	a[startI+s1I+1] = a[startPrevI+s1I] + 1;
      }
      else {
	int idxA = startI+s1I;
	int idxB = startPrevI+s1I+1;
	a[startI+s1I+1] = MAX(a[idxA], a[idxB]);
      }
      //std::cerr << a[startI+s1I+1] << " ";
    }
    prevColumn = 1-prevColumn;
    //std::cerr << std::endl;
  }

  int ret = a[prevColumn*(len+1)+len];
  delete[] a;
  return ret;
}

int main() {
  char *line1 = new char[LINE_LENGTH];
  char *line2 = new char[LINE_LENGTH];

  int cases;
  scanf("%d\n", &cases);

  for(int cas = 0; cas < cases; ++cas) {
    gets(line1);
    int size = strlen(line1);
    std::copy(line1, line1+size, line2);
    std::reverse(line1, line1+size);
    line1[size] = '\0';
    line2[size] = '\0';
    //std::cerr << line1 << " VS " << line2 << ", len=" << size << std::endl;
    
    std::cout << longestSubSequence(line1, line2, size) << std::endl;    
  }
  return 0;
}
