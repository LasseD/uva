#include <iostream>
#include <stdio.h>

int main() {
  int signals[100];
  while(true) {
    // read signals:
    int numSignals = 0;
    int minSignal = 9000;
    while(true) {
      int signal;
      std::cin >> signal;
      if(signal == 0)
	break;
      signals[numSignals] = signal;
      ++numSignals;
      if(signal < minSignal)
	minSignal = signal;
    }
    if(numSignals == 0)
      return 0;
    // simulate:
    int okk = false;
    for(int time = 2*minSignal; time <= 5*60*60;) {
      //Check if all green:
      bool ok = true;
      for(int i = 0; i < numSignals; ++i) {
	int in = time % (2*signals[i]);
	if(in >= signals[i]-5) {
	  //std::cerr << i << " not green at time " << time << std::endl;
	  ok = false;
	  break;
	}	  
      }
      if(ok) {
	//std::cerr << "All green at time " << time << std::endl;
	printf("%02i:%02i:%02i\n", time / 3600, (time / 60) % 60, time % 60);
	okk = true;
	break;
      }

      // Find next green:
      int toNextGreen = 90;
      for(int i = 0; i < numSignals; ++i) {
	int in = (2*signals[i]) - time % (2*signals[i]);
	if(in < toNextGreen) {
	  toNextGreen = in;
	}	  
      }
      time += toNextGreen;
    }
    if(!okk) {
      std::cout << "Signals fail to synchronise in 5 hours" << std::endl;
    }
  }
}
