#include <iostream>
#include <stdio.h>
#include <string>
#include <stack>

std::string readLine(std::stack<char> &s) {
  char line[150];
  gets(line);
  char c;
  for(int i = 0; isprint(c = line[i]); ++i) {
    if(c >= '0' && c <= '9')
      s.push(c);
  }
  return std::string(line);
}

bool accept(std::string *solution, int n, std::string *team, int m) {
  if(n != m)
    return false;
  for(int i = 0; i < n; ++i) {
    if(solution[i].compare(team[i]) != 0)
      return false;
  }
  return true;
}

bool pe(std::stack<char> &a, std::stack<char> &b) {
  if(a.size() != b.size())
    return false;
  while(!a.empty()) {
    if(a.top() != b.top())
      return false;
    a.pop();
    b.pop();
  }
  return true;
}

unsigned int readUInt() {
  unsigned int ret = 0;

  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return ret;
}

int main() {
  std::string solution[100], team[100];
  for(int cas = 1;; ++cas) {
    unsigned int n = readUInt();
    if(n == 0)
      return 0;
    std::stack<char> solutionStack, teamStack;
    for(unsigned int i = 0; i < n; ++i)
      solution[i] = readLine(solutionStack);
    unsigned int m = readUInt();
    for(unsigned int i = 0; i < m; ++i)
      team[i] = readLine(teamStack);
    
    std::cout << "Run #" << cas << ": ";
    if(accept(solution, n, team, m)) {
      std::cout << "Accepted" << std::endl;
    }
    else if(pe(solutionStack, teamStack)) {
      std::cout << "Presentation Error" << std::endl;
    }
    else {
      std::cout << "Wrong Answer" << std::endl;
    }
  }
}
