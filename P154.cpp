#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>

typedef std::pair<char,char> cc;

int main() {
  std::vector<std::vector<cc> > v;

  while(true) {
    std::string line;
    getline(std::cin, line);
    if(line[0] == '#')
      return 0;
    if(line[0] != 'e') {
      std::vector<cc> row;
      for(int i = 0; i < 5; ++i) {
	cc c(line[4*i], line[4*i+2]);
	row.push_back(c);
      }
      std::sort(row.begin(), row.end());      
      v.push_back(row);
    }
    else { // process:!
      //std::cerr << "Starting processing with " << v.size() << " cities" << std::endl;
      int best = 0;
      int bestSum = 5*100*2; // large
      for(unsigned int i = 0; i < v.size(); ++i) {
	int sum = 0;
	std::vector<cc> row1 = v[i];
	for(unsigned int j = 0; j < v.size(); ++j) {
	  if(i == j)
	    continue;
	  std::vector<cc> row2 = v[j];
	  for(int k = 0; k < 5; ++k) {
	    if(row1[k].second != row2[k].second)
	      ++sum;
	  }
	}
	//std::cerr << "City " << i << " causes " << sum << " changes" << std::endl;
	if(sum < bestSum) {
	  //std::cerr << "City " << i << " with " << sum << " changes is best yet!" << std::endl;
	  best = i;
	  bestSum = sum;
	}
      }
      std::cout << (best+1) << std::endl;
      v.clear();
    }
  }
}
