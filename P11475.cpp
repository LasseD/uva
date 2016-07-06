#include <iostream>
#include <stdio.h>

#define LINE_LENGTH 200008

void die() {
  int *a = NULL;
  a[6]=42;
}

/*
Extend to palindrome.
https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 */
int main() {
  char *line = new char[LINE_LENGTH+1];
  int *kmpTable = new int[LINE_LENGTH/2];
  kmpTable[0] = -1;
  kmpTable[1] = 0;

  while(gets(line)) {
    int size = 0;
    while(isalpha(line[size]))
      ++size;
    line[size] = '\0';
    line[LINE_LENGTH] = '\0';
    
    int currentMatchInLineIndex = 0; // m in kmp_search
    int reverseI = 0; // i in kmp_search
    int kmpTableI = 2; // pos in kmp_search
    int cnd = 0; // Used for kmpTable.
    //std::cerr << "Size=" << size << ", line=" << line << std::endl;

    int copyTo = size;
    while(reverseI + currentMatchInLineIndex < size) {
      if(line[currentMatchInLineIndex+reverseI] == line[size-1-reverseI]) {
	if(reverseI + currentMatchInLineIndex + 1 == size) {
	  copyTo = currentMatchInLineIndex;
	  break;
	}
	++reverseI;
      }
      else { // Character doesn't match, reset:
	while(reverseI >= kmpTableI) {
	  if(line[size-1-kmpTableI+1] == line[size-1-cnd]) {
	    kmpTable[kmpTableI] = cnd+1;
	    cnd++;
	    kmpTableI++;
	  }
	  else if(cnd > 0)
	    cnd = kmpTable[cnd];
	  else
	    kmpTable[kmpTableI++] = 0;
	}

	if(kmpTable[reverseI] > -1) {
	  currentMatchInLineIndex+=reverseI-kmpTable[reverseI];
	  if(currentMatchInLineIndex < 0)
	    die();
	  reverseI = kmpTable[reverseI];
	}
	else {
	  currentMatchInLineIndex++;
	  reverseI = 0;
	}
      }
    }

    //std::cerr << "size=" << size << ", s=" << line << ", m=" << currentMatchInLineIndex << ", i=" << reverseI << ", copyTo=" << copyTo << std::endl;
    // Found!
    // Build stack!
    for(int i = 0; i < copyTo; ++i)
      line[LINE_LENGTH-1-i] = line[i];
    std::cout << line << &line[LINE_LENGTH-copyTo] << std::endl;    
  }
  delete[] line;
  delete[] kmpTable;
  return 0;
}
