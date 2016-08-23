#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stack>

typedef std::pair<int,int> PP;
typedef std::stack<PP> Stack;

int main() {
  int X, Y, Y1, Y2, X1, X2, N = 0, M = 0; // M wide, N tall.
  char pixels[251*251];
  std::string s, command, C;  
  while(std::getline(std::cin,s)) {
    Stack stack;
    std::stringstream ss;
    ss << s;
    ss >> command;
    switch(command[0]) {
    case 'I':
      ss >> M >> N;
    case 'C':
      for(int y = 0; y < N; ++y)
	for(int x = 0; x < M; ++x)
	  pixels[y*M+x] = 'O'; // O 0x4F as in "Opening".
      break;
    case 'L':
      ss >> X >> Y >> C;
      pixels[(Y-1)*M+X-1] = C[0];
      break;
    case 'V':
      ss >> X >> Y1 >> Y2 >> C;
      if(Y1 > Y2)
	std::swap(Y1,Y2);
      for(int y = Y1-1; y < Y2; ++y)
	pixels[y*M+X-1] = C[0];
      break;
    case 'H':
      ss >> X1 >> X2 >> Y >> C;
      if(X1 > X2)
	std::swap(X1,X2);
      for(int x = X1-1; x < X2; ++x)
	pixels[(Y-1)*M+x] = C[0];
      break;
    case 'K':
      ss >> X1 >> Y1 >> X2 >> Y2 >> C;
      if(X1 > X2)
	std::swap(X1,X2);
      if(Y1 > Y2)
	std::swap(Y1,Y2);
      for(int y = Y1-1; y < Y2; ++y)
	for(int x = X1-1; x < X2; ++x)
	  pixels[y*M+x] = C[0];
      break;
    case 'F':
      ss >> X >> Y >> C;
      //std::cerr << "Filling " << color << " to " << C << std::endl;
      stack.push(PP(X-1,Y-1));
      while(!stack.empty()) {
	PP p = stack.top();
	//std::cerr << " to " << p.first << "," << p.second << std::endl;
	stack.pop();
	char prevColor = pixels[p.second*M+p.first];
	if(prevColor == C[0])
	  continue;
	if(p.first > 0 && pixels[p.second*M + p.first-1] == prevColor)
	  stack.push(PP(p.first-1, p.second));
	if(p.first < M-1 && pixels[p.second*M + p.first+1] == prevColor)
	  stack.push(PP(p.first+1, p.second));
	if(p.second > 0 && pixels[(p.second-1)*M + p.first] == prevColor)
	  stack.push(PP(p.first, p.second-1));
	if(p.second < N-1 && pixels[(p.second+1)*M + p.first] == prevColor)
	  stack.push(PP(p.first, p.second+1));
	pixels[p.second*M+p.first] = C[0];
      }
      break;
    case 'S':
      ss >> C;
      std::cout << C << std::endl;
      for(int y = 0; y < N; ++y) {
	for(int x = 0; x < M; ++x) {
	  std::cout << pixels[y*M+x];
	}
	std::cout << std::endl;
      }
      break;
    case 'X':
      return 0;
      break;
    }
  }
}
