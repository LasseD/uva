#include <iostream>
#include <stdio.h>

bool getTime(int &m, int &h) {
  char line[10];
  std::cin.getline(line, 10);
  h = line[0]-'0';
  int i = 2;
  if(line[1] != ':') {
    ++i;
    h = 10*h + (line[1]-'0');
  }
  m = 10*(line[i]-'0') + (line[i+1]-'0');
  return !(h == 0 && m == 0);
}

int main() {
  int m, h;
  while(getTime(m,h)) {
    double aM = 360*m/(double)60;
    double aH = 360*(h/(double)12 + m/(double)(12*60));
    double aDiff = aM-aH;
    while(aDiff < 0)
      aDiff += 360;
    while(aDiff > 360)
      aDiff -= 360;
    if(aDiff > 180)
      aDiff = 360-aDiff;
    printf("%.3f\n", aDiff);
  }
  return 0;
}
