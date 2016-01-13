#include <iostream>
#include <stdio.h>

#define MAX(a,b) ((a) < (b) ? (b) : (a))

int longestSubSequence(char const * const s1, int lenS1, char const * const s2, int lenS2) {
  if(lenS1 == 0 || lenS2 == 0)
    return 0;
  int *a = new int[2*(lenS1+1)]; // +1 for empty first character. 
  int prevColumn = 0;
  for(int i = 0; i <= lenS1; ++i)
    a[i] = 0;
  for(int s2I = 0; s2I < lenS2; ++s2I) {
    int startI = (1-prevColumn)*(lenS1+1);
    int startPrevI = prevColumn*(lenS1+1);
    a[startI] = 0; // empty first character.
    for(int s1I = 0; s1I < lenS1; ++s1I) {
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

  int ret = a[prevColumn*(lenS1+1)+lenS1];
  delete[] a;
  return ret;
}

int len(char *s) {
  int ret = 0;
  while(isprint(s[ret]))
    ++ret;
  return ret;
}

int main() {
  char s1[1009], s2[1009];
  while(gets(s1)) {
    gets(s2);
    std::cout << longestSubSequence(s1, len(s1), s2, len(s2)) << std::endl;
  }
  return 0;
}
