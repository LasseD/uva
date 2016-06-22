#include <iostream>
#include <stdio.h>

/*
Minimize values. 
Vovel,consonant,vovel,consonant,...
Consonant repeat max: 5
Vowel repeat max: 21
 */
int main() {
  int N, n;
  char vowels[5] = {'A','U','E','O','I'}; 
  char consonants[21] = {'J','S',
		      'B','K','T', 
		      'C','L',
		      'D','M','V',
		      'N','W',
		      'F','X',
		      'G','P','Y',
		      'H','Q','Z',
		      'R'}; 
  int vCounts[26], cCounts[26];
  for(int i = 0; i < 26; ++i)
    vCounts[i] = cCounts[i] = 0;
  
  std::cin >> N; // Cases.
  for(int cas = 1; cas <= N; ++cas) {
    std::cin >> n; // Name length.
    for(int i = 0; i < n; ++i) {
      if(i % 2 == 1) { // Consonant:
	++cCounts[consonants[(i / 2) / 5]-'A'];
      }
      else { // Vowels:
	++vCounts[vowels[(i / 2) / 21]-'A'];
      }
    }
    std::cout << "Case " << cas << ": ";
    int vI = 0;
    int cI = 0;
    for(int i = 0; i < n; ++i) {
      if(i % 2 == 1) { // Consonant:
	while(cCounts[cI] == 0)
	  ++cI;
	--cCounts[cI];
	std::cout << (char)('A'+cI);
      }
      else { // Vowels:
	while(vCounts[vI] == 0)
	  ++vI;
	--vCounts[vI];
	std::cout << (char)('A'+vI);
      }
    }
    std::cout << std::endl;
  }
  return 0;
}
