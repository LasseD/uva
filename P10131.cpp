#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>

#define WEIGHT first
#define IQ second
#define ELEPHANT first
#define IDX second
typedef std::pair<int,int> Elephant; // weight, iQ
typedef std::pair<Elephant,int> EI; // Elephant, idx.

void run(std::vector<EI> &elephants) {
  std::sort(elephants.begin(), elephants.end());

  int *bestSizes = new int[elephants.size()]; // Best subset that include elephant i.
  bestSizes[0] = 1; // First can take itself.

  int *prev = new int[elephants.size()];  
  prev[0] = -1;

  int bestSize = 1;
  int bestLastElephant = 0;
  
  //std::cerr << "By weight: " << std::endl;
  for(unsigned int i = 1; i < elephants.size(); ++i) {
    int bestPrevI = -1;
    int bestSizeI = 1;

    int iqI = elephants[i].ELEPHANT.IQ;
    int weightI = elephants[i].ELEPHANT.WEIGHT;
    //std::cerr << weightI << "/" << iqI << ", idx " << elephants[i].IDX << std::endl;

    for(unsigned int j = 0; j < i; ++j) { 
      int iqJ = elephants[j].ELEPHANT.IQ;
      int weightJ = elephants[j].ELEPHANT.WEIGHT;

      if(bestSizes[j] >= bestSizeI && weightJ < weightI && iqJ > iqI) {
	bestSizeI = bestSizes[j]+1;
	bestPrevI = j;
      }
    }
    bestSizes[i] = bestSizeI;
    prev[i] = bestPrevI;
    if(bestSizeI > bestSize) {
      bestSize = bestSizeI;
      bestLastElephant = i;
    }
  }
  std::cout << bestSize << std::endl;
  std::stack<int> s;
  while(bestLastElephant != -1) {
    s.push(elephants[bestLastElephant].IDX);
    bestLastElephant = prev[bestLastElephant];
  }
  while(!s.empty()) {
    std::cout << s.top() << std::endl;
    s.pop();
  }

  delete[] bestSizes;
  delete[] prev;
}

int main() {
  std::vector<EI> elephants;
  int weight, iq;
  int i = 1;
  
  while(std::cin >> weight) {
    std::cin >> iq;
    elephants.push_back(EI(Elephant(weight,iq),i++));
  }
  run(elephants);  
}
