#include <iostream>

int main() {
  int n;
  char w1[20], w2[20];
  while(true) { // Iterate games:
    bool cheating = false;
    int min = 1;
    int max = 10;
    while(true) {
      std::cin >> n;
      if(n == 0)
	return 0;
      std::cin >> w1 >> w2; // new guess.
      if(w1[0] == 'r') {
	if(n > max || n < min)
	  cheating = true;
	if(cheating)
	  std::cout << "Stan is dishonest" << std::endl;
	else
	  std::cout << "Stan may be honest" << std::endl;
	break;
      }
      if(w2[0] == 'h') {
	if(n <= min)
	  cheating = true;
	if(n-1 < max)
	  max = n-1;
      }
      else {
	if(n >= max)
	  cheating = true;
	if(n+1 > min)
	  min = n+1;
      }
    } // while each round.
  } // while... Each game
  return 0;
}
