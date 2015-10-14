#include <iostream>

bool readInts(int &a, int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  char w[20];
  if(!std::cin.getline(w, 20))
    return false;
  for(int i = 0; i < 20; ++i) {
    if(w[i] == '-') {
      if(!aStarted) {
	aStarted = true;
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
  //std::cerr << "Read " << a << ", " << b << std::endl;
  return true;
}

int main() {
  int X, Y;
  while(readInts(X, Y)) {
    std::cout << ((Y-1)/(Y-X)+1) << std::endl;
  }
}
