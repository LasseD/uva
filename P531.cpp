#include <iostream>
#include <stdio.h>
#include <vector>
#include <stack>

typedef std::string String;
typedef std::vector<String> Vector;
typedef std::stack<int> Stack;

#define MAX(a,b) ((a) < (b) ? (b) : (a))

void printLongestSubSequence(const Vector &s1, const Vector &s2) {
  unsigned int lenS1 = s1.size();
  unsigned int lenS2 = s2.size();
  if(lenS1 == 0 || lenS2 == 0)
    return;
  int *a = new int[(lenS2+1)*(lenS1+1)]; // +1 for empty first string. 
  int *prev = new int[(lenS2+1)*(lenS1+1)];
  //int *asi = new int[(lenS2+1)*(lenS1+1)]; // String index in si where the addition for given index is increased.
  for(unsigned int i = 0; i <= lenS1; ++i) {
    a[i] = 0; // Empty first sequence
    prev[i] = -1;
    //asi[i] = -1;
  }
  int bestI = 0;
  for(unsigned int s2I = 0; s2I < lenS2; ++s2I) {
    int startI = (s2I+1)*(lenS1+1);
    int startPrevI = s2I*(lenS1+1);
    a[startI] = 0; // empty first string.
    prev[startI] = -1; // empty first string.
    //asi[startI] = -1; // empty first string.
    for(unsigned int s1I = 0; s1I < lenS1; ++s1I) {
      if(s1[s1I] == s2[s2I]) {
	a[startI+s1I+1] = a[startPrevI+s1I] + 1;
	prev[startI+s1I+1] = startPrevI+s1I;
	if(a[startI+s1I+1] > a[bestI])
	  bestI = startI+s1I+1;
	//asi[startI+s1I+1] = s1I;
      }
      else {
	int idxA = startI+s1I;
	int idxB = startPrevI+s1I+1;
	if(a[idxA] < a[idxB]) {
	  a[startI+s1I+1] = a[idxB];
	  prev[startI+s1I+1] = idxB;
	}
	else {
	  a[startI+s1I+1] = a[idxA];
	  prev[startI+s1I+1] = idxA;
	}
	//asi[startI+s1I+1] = -1;
      }
      //std::cerr << a[startI+s1I+1] << " ";
    }
    //std::cerr << std::endl;
  }

  //int ret = a[lenS2*(lenS1+1)+lenS1];
  Stack s;
  while(prev[bestI] != -1) {
    //std::cerr << "BestI=" << bestI << std::endl;
    if(a[prev[bestI]] != a[bestI])
      s.push(-1 + bestI % (lenS1+1));
    bestI = prev[bestI];
  }

  while(!s.empty()) {
    int str = s.top();
    s.pop();
    std::cout << s1[str];
    if(!s.empty())
      std::cout << " ";
  }
  std::cout << std::endl;

  delete[] a;
  delete[] prev;
  //delete[] asi;
}

bool fillVector(Vector &v) {
  String s;
  while(std::cin >> s) {
    if(s[0] == '#' && s.size() == 1) {
      //std::cerr << "DONE READ" << std::endl << std::endl;
      return true;
    }
    //std::cerr << " '" << s << "'";
    v.push_back(s);
  }
  return false;
}

int main() {
  while(true) {
    Vector s1, s2;
    if(!fillVector(s1))
      return 0;
    fillVector(s2);
    printLongestSubSequence(s1, s2);
  }
}
