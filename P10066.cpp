#include <iostream>
#include <stdio.h>

#define MAX(a,b) ((a) < (b) ? (b) : (a))

int longestSubSequence(short const * const s1, int lenS1, short const * const s2, int lenS2) {
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

int main() {
  short s1[102], s2[102];
  int lenS1, lenS2;
  for(int cas = 1; true; ++cas) {
    std::cin >> lenS1 >> lenS2;
    if(lenS1 == 0 && lenS2 == 0)
      return 0;
    for(int i = 0; i < lenS1; ++i)
      std::cin >> s1[i];
    for(int i = 0; i < lenS2; ++i)
      std::cin >> s2[i];
    std::cout << "Twin Towers #" << cas << std::endl;
    std::cout << "Number of Tiles : " << longestSubSequence(s1, lenS1, s2, lenS2) << std::endl;
    std::cout << std::endl;
  }
}
