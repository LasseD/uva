#include <iostream>
#include <ctype.h>

bool readInts(int &a, int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  bool negA = false;
  char w[20];
  if(!std::cin.getline(w, 20))
    return false;
  for(int i = 0; i < 20; ++i) {
    if(w[i] == '-') {
      if(!aStarted) {
	aStarted = true;
	negA = true;
      }
    }      
    else if(w[i] >= '0' && w[i] <= '9') {
      if(aDone)
	b = b*10 + (w[i]-'0');
      else {
	a = a*10 + (w[i]-'0');
	aStarted = true;
      }
    }
    else {
      if(!isprint(w[i]))
	break;
      if(aStarted)
	aDone = true;
    }
  }
  if(negA)
    a = -a;
  //std::cerr << "Read " << a << ", " << b << std::endl;
  return true;
}

/*
  Velocity after time t: v
  Displacement after time t: x0 = ½at^2, since v=at => a=v/t => x0 = ½v/t*t^2 = ½vt
  Velocity after time 2t: 2v
  Displacement after time 2t: ½a(2t)^2 = ½v/t(2t)^2 = ½v/t*4*t*t = 2vt
 */
int main() {
  int v, t;
  while(readInts(v, t)) {
    std::cout << (v * 2 * t) << std::endl;
  }
  return 0;
}
