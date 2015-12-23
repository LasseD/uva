#include <iostream>

bool readInts(int &a, int &b) {
  a = b = 0;
  bool aStarted = false;
  bool aDone = false;
  char w[20];
  if(!std::cin.getline(w, 20))
    return false;
  for(int i = 0; i < 20; ++i) {
    if(w[i] >= '0' && w[i] <= '9') {
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
  return true;
}

int cuts(int *buf, int a, int b) {
  if(a > b)
    return cuts(buf, b, a);
  if(a == 1)
    return b-1;
  int idx = (a-1)*300+b-1;
  if(buf[idx] != -1)
    return buf[idx];
  return buf[idx] = cuts(buf, a, b/2) + cuts(buf, a, b-b/2) + 1;
}

int main() {
  int N, M;
  int buf[90000];
  for(int i = 0; i < 90000; ++i)
    buf[i] = -1;
  while(readInts(N, M)) {
    std::cout << cuts(buf, N,M) << std::endl;
  }
  return 0;
}
