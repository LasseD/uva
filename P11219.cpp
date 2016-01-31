#include <iostream>
#include <stdio.h>

void readDate(char *w, int &y, int &m, int &d) {
  d = 10*(w[0]-'0')+(w[1]-'0');
  m = 10*(w[3]-'0')+(w[4]-'0');
  y = 1000*(w[6]-'0')+100*(w[7]-'0')+10*(w[8]-'0')+(w[9]-'0');
  //std::cerr << "Date: " << d << "/" << m << "/"  << y << std::endl;
}

int diffYears(int y1, int m1, int d1, int y2, int m2, int d2) {
  int ret = y2-y1;
  if(m2 < m1 || (m2 == m1 && d2 < d1))
    --ret;
  //std::cerr << "Diff years: " << ret << std::endl;
  return ret;
}

int main() {
  // Read cases:
  char c, w[20];
  int cases = 0;
  gets(w);
  for(int i = 0; isdigit(c = w[i]); ++i)
    cases = 10 * cases + (c-'0');
  for(int cas = 1; cas <= cases; ++cas) {
    std::cout << "Case #" << cas << ": ";
    int y1, m1, d1, y2, m2, d2; // 1:current date, 2: birth date
    gets(w);
    gets(w);
    readDate(w, y1, m1, d1);
    gets(w);
    readDate(w, y2, m2, d2);    
    if(y1==y2 && m1==m2 && d1==d2) {
      std::cout << 0 << std::endl;
    }
    else if(y2 > y1 || (y2 == y1 && (m2 > m1 || (m2 == m1 && d2 > d1)))) {
      std::cout << "Invalid birth date" << std::endl;      
    }
    else {
      int years = diffYears(y2,m2,d2, y1,m1,d1);
      if(years > 130)// || (years == 130 && (m1!=m2||d1!=d2))) Problem description is vague!
	std::cout << "Check birth date" << std::endl;      
      else
	std::cout << years << std::endl;
    }
  }
  return 0;
}
