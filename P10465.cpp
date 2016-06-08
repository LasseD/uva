#include <iostream>
#include <stdio.h>

int main() {
  int n, m, t;
  while(std::cin >> n >> m >> t) {
    if(m < n)
      std::swap(n, m);

    int bestBurgers = 0;
    int bestBeerTime = t;

    for(int countM = 0; countM*m <= t; ++countM) {
      int countN = (t-countM*m)/n;
      int beerTime = t - countM*m - countN*n;
      if(beerTime < bestBeerTime || (beerTime == bestBeerTime && countN+countM > bestBurgers)) {
	bestBeerTime = beerTime;
	bestBurgers = countN+countM;
      }
    }
    std::cerr << "n=" << n << ", m=" << m << ", t=" << t << std::endl;
    std::cout << bestBurgers;
    if(bestBeerTime > 0)
      std::cout << " " << bestBeerTime;
    std::cout << std::endl;
  }
  return 0;
}
