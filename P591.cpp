#include <iostream>

int main() {
  int n, h;
  int wall[50];
  for(int trial = 0; true; ++trial) {
    std::cin >> n;
    if(n == 0)
      return 0;
    int sum = 0;
    for(int i = 0; i < n; ++i) {
      std::cin >> h;
      wall[i] = h;
      sum += h;
    }
    int avg = sum/n;
    int diff = 0;
    for(int i = 0; i < n; ++i) {
      if(wall[i] > avg) {
	diff += wall[i]-avg;
      }
    }
    std::cout << "Set #" << (trial+1) << std::endl;
    std::cout << "The minimum number of moves is " << diff << "." << std::endl << std::endl;
  }
}
