#include <iostream>

int main() {
  bool regions[100]; // with light;
  regions[0] = false;

  while(true) {
    int N;
    std::cin >> N;
    if(N == 0)
      return 0;
    //std::cerr << "Running N: " << N << std::endl;    
    
    // Try all:
    for(int m = 1; m <= N; ++m) {
      for(int i = 1; i < N; ++i)
	regions[i] = true;
      int lighted = N-1;
      int i = 0;
      //std::cerr << m << "=>";
      while(lighted > 1) {
	//std::cerr << " " << (i+1);
	for(int j = 0; j < m; ++j) {
	  ++i;
	  if(i == N)
	    i = 0;
	  while(!regions[i]) {
	    ++i;
	    if(i == N)
	      i = 0;
	  }	  
	}
	regions[i] = false;
	if(i == 12)
	  break;
	--lighted;
      }
      //std::cerr << std::endl;//*/
      if(regions[12]) {
	std::cout << m << std::endl;      
	break;
      }
    }
  }
}
