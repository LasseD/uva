#include <stdio.h>
#include <iostream>
#include <sstream>

typedef std::string String;
typedef std::stringstream SS;

int main() {
  String line, w;
  int speed, time, prevTime = 0, prevSpeed = 0;
  long dist = 0;
  while(std::getline(std::cin,line)) {
    SS ss; ss << line; ss >> w;
    time = 
      36000*(w[0]-'0')+
      3600*(w[1]-'0')+
      600*(w[3]-'0')+
      60*(w[4]-'0')+
      10*(w[6]-'0')+
      1*(w[7]-'0');
    dist += (time-prevTime)*prevSpeed;
    prevTime = time;

    if(ss >> speed)
      prevSpeed = speed;
    else
      printf("%s %.2f km\n", w.c_str(), dist / 3600.0);
  }
  return 0;
}
