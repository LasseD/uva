#include <iostream>
#include <stdio.h>
#include <stack>

int ctoi(char c) {
  switch(c) {
  case 'A':
    return 0;
  case 'K':
    return 12;
  case 'Q':
    return 11;
  case 'J':
    return 10;
  case 'T':
    return 9;
  default:
    return c-'0'-1;
  }
}

int main() {
  while(true) {
    std::stack<std::pair<int, std::string> > stacks[13];

    // read cards:
    std::string card;
    std::stack<std::string> inStack;
    for(int i = 0; i < 4*13; ++i) {
      std::cin >> card;
      if(card[0] == '#')
	return 0;
      inStack.push(card);
    }
    int stackI = 0;
    while(!inStack.empty()) {
      card = inStack.top();
      inStack.pop();
      int val = ctoi(card[0]);
      //std::cerr << "Reading " << card << " -> " << val << std::endl;
      stacks[stackI].push(std::make_pair(val, card));
      ++stackI;
      if(stackI == 13)
	stackI = 0;
    }
    // play:
    int currentVal = stacks[12].top().first;
    std::string lastExposed = stacks[12].top().second;
    //std::cerr << "Start Exposing " << lastExposed << " from stack 12 -> " << currentVal << std::endl;
    stacks[12].pop();
    int exposed = 1;
    while(!stacks[currentVal].empty()) {
      int v = stacks[currentVal].top().first;
      lastExposed = stacks[currentVal].top().second;
      stacks[currentVal].pop();
      //std::cerr << "Exposing " << lastExposed << " from stack " << currentVal << " -> " << v << std::endl;
      currentVal = v;
      ++exposed;
    }
    printf("%02i,%s\n", exposed, lastExposed.c_str());
  }
}
