#include <iostream>
#include <stdio.h>

/*
Problem: Compute last digit of m^n.
 */
int main() {
  char w[309];
  while(true) {
    gets(w);
    int j = 0; while(!isdigit(w[j])) ++j;
    int iM = j;
    int lenM = 0; while(isdigit(w[j])) {++j;++lenM;};
    while(!isdigit(w[j])) ++j;
    int iN = j;
    int lenN = 0; while(isdigit(w[j])) {++j;++lenN;};
    
    //std::cin >> sm >> sn;
    int lastDigitM = w[iM+lenM-1]-'0';
    int nMod100 = w[iN+lenN-1]-'0';
    if(lenN > 1)
      nMod100 += 10*(w[iN+lenN-2]-'0');
    if(lenN == 1 && nMod100 == 0) {
      if(lenM == 1 && lastDigitM == 0)
	return 0;
      w[0] = '1';
      w[1] = '\0';
      puts(w);
      continue;
    }
    int ret = lastDigitM;
    for(int i = 0; i < (nMod100+3) % 4; ++i)
      ret*=lastDigitM;
    w[0] = '0' + ret%10;
    w[1] = '\0';
    puts(w);
  }
}
