#include <iostream>
#include <stdio.h>

int readInt(const std::string line) {
  int ret = 0;
  for(unsigned int i = 0; true; ++i) {
    char c = line[i];
    if(c == '.' || c == ',') {
      continue;
    }
    if(c >= '0' && c <= '9') {
      ret = 10*ret + (c-'0');
      continue;
    }
    //std::cerr << "Read " << ret << std::endl;
    return ret;
  }
}

int computeFor(int low, int high, int N, int *paid) {
  int paidTotal = 0;
  int bank = 0;
  for(int i = 0; i < N; ++i) {
    if(paid[i] <= low) {
      int pay = low - paid[i];
      paidTotal += pay;
      bank += pay;
    }
    else {
      int receive = paid[i] - high;
      bank -= receive;
    }
  }
  if(bank < 0)
    paidTotal -= bank; // More needs to be paid!
  return paidTotal;
}

/*
Make paying for the trip fair for all students.
 */
int main() {
  while(true) {
    // Parse input:
    std::string line;
    std::getline(std::cin, line);

    int N = readInt(line);
    if(N == 0)
      return 0;

    int paid[10000];
    int sum = 0;
    for(int i = 0; i < N; ++i) {
      std::getline(std::cin, line);      
      int val = readInt(line);
      paid[i] = val;
      sum += val;
    }

    // Compute output:
    int avg = (sum+N/2)/N;
    //std::cerr << " AVERAGE: " << avg << std::endl;
    int pay1 = computeFor(avg-1, avg, N, paid);
    int pay2 = computeFor(avg, avg+1, N, paid);
    int pay = pay1 < pay2 ? pay1 : pay2;

    //std::cerr << " TOTAL TRANSACTION: " << pay << std::endl;
 
    printf("$%i.%02i\n", pay/100, pay%100);
    //std::cerr << " " << pay << std::endl;
  }
}
