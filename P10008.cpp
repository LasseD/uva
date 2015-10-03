#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>

#define MAX_LINE_LENGTH 2000

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[MAX_LINE_LENGTH];
  std::cin.getline(w, MAX_LINE_LENGTH);
  int i = 0;
  for(; isprint(w[i]); ++i) {
    if(w[i] >= '0' && w[i] <= '9')
      ret = ret * 10 + (w[i]-'0');
  }
  if(i >= MAX_LINE_LENGTH) {
    int *die = NULL;
    die[42] = 666;
  }  
  return ret;
}

void readLineAndCountLetters(long *counts) {
  char w[MAX_LINE_LENGTH];
  std::cin.getline(w, MAX_LINE_LENGTH);

  int i = 0;
  for(; isprint(w[i]); ++i) {
    if(w[i] >= 'a' && w[i] <= 'z') {
      ++counts[w[i]-'a'];
    }    
    else if(w[i] >= 'A' && w[i] <= 'Z') {
      ++counts[w[i]-'A'];
    }
  }
  if(i >= MAX_LINE_LENGTH) {
    int *die = NULL;
    die[42] = 666;
  }  
}

int main() {
  long counts[26];
  for(int i = 0; i < 26; ++i)
    counts[i] = 0;

  // Read n:
  unsigned int n = readUInt();

  // Read lines:
  for(unsigned int i = 0; i < n; ++i) {
    readLineAndCountLetters(counts);
  }

  // Compute counts, sort and output:
  std::vector<std::pair<long,char> > v;
  for(int i = 0; i < 26; ++i) {
    if(counts[i] != 0)
      v.push_back(std::make_pair(-counts[i], 'A'+i));
  }
  std::sort(v.begin(), v.end());
  
  for(std::vector<std::pair<long,char> >::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << it->second << " " << (-it->first) << std::endl;
  }

  return 0;
}
