#include <iostream>
#include <cmath>

int main() {
  double T;
  int N;
  std::cin >> T;
  std::cin >> N;
  int *vegs = new int[N];  
  for(int i = 0; i < N; ++i) {
    int a;
    std::cin >> a;
    //std::cerr << a << " ";
    vegs[i] = a;
  }
  //std::cerr << std::endl;
  
  int best = 500;
  for(int i = 0; i < N; ++i) {
    int veg = vegs[i];
    for(int initialCuts = 0; initialCuts < 500; ++initialCuts) {
      double max_size = veg/(double)(initialCuts+1);
      int cuts = initialCuts;
      for(int j = 0; j < N && cuts < 500; ++j) {	
	if(i == j)
	  continue;
	int vegj = vegs[j];

	int parts = ceil(vegj/max_size);
	if(vegj < T*max_size*parts) {
	  cuts = 500;
	}
	else
	  cuts += parts-1;	
      }
      if(cuts < best)
	best = cuts;
    }
  }
  std::cout << best << std::endl;
  return 0;
}
