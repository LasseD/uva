#include <iostream>

int priceMiles(int duration) {
  return 10*(1+duration/30);
}
int priceJuice(int duration) {
  return 15*(1+duration/60);
}

int main() {
  int cases, N, durations[20];
  std::cin >> cases;
  for(int cas = 1; cas <= cases; ++cas) {
    std::cin >> N;
    int sumMiles = 0;
    int sumJuice = 0;
    for(int i = 0; i < N; ++i) {
      std::cin >> durations[i];
      sumMiles += priceMiles(durations[i]);
      sumJuice += priceJuice(durations[i]);
    }
    if(sumMiles < sumJuice) 
      std::cout << "Case " << cas << ": Mile " << sumMiles << std::endl;
    else if(sumMiles > sumJuice) 
      std::cout << "Case " << cas << ": Juice " << sumJuice << std::endl;
    else
      std::cout << "Case " << cas << ": Mile Juice " << sumJuice << std::endl;
  }
}
