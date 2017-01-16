#include <stdio.h>
#include <iostream>
#include <stack>

using namespace std;

bool isOp(char c) {
  switch(c) {
  case '+':
  case '-':
  case '*':
  case '/':
    return true;
  default:
    return false;
  }
}

bool isOK(char c) {
  return isdigit(c) || isOp(c) || c == '(' || c == ')';
}

// Dijkstra's Shunting yard algorithm. Infix -> postfix math expressions.
// Notice / and - are only left associative
int main() {
  int N = 0; 
  char c, line[39];
  gets(line);
  int j = 0;
  while(isdigit(c = line[j++]))
    N = 10*N+(c-'0');

  //scanf("%d\n", &N);
  //cerr << N << " cases!" << endl;
  gets(line);

  for(int cas = 0; cas < N; ++cas) {
    if(cas != 0)
      cout << endl;
    stack<char> s;
    while(gets(line) && isOK(c = line[0])) {
      //cerr << "Handling " << c << endl;
      if(isdigit(c)) {
	cout << c;
      }
      else if(c == '(') {
	s.push(c);
      }
      else if(c == ')') {
	while((c = s.top()) != '(') {
	  cout << c;
	  s.pop();
	}
	s.pop(); // '('
      }
      else { // + - * /
	while(!s.empty()) {
	  char c2 = s.top();
	  if(!isOp(c2))
	    break;
	  if(c == '+' || c == '-' || ((c == '/' || c == '*') && !(c2 == '+' || c2 == '-'))) {
	    cout << c2;
	    s.pop();
	  }
	  else 
	    break;
	}
	s.push(c);
      }
    } // while gets.
    
    while(!s.empty()) {
      cout << s.top();
      s.pop();
    }
    cout << endl;
  }
  return 0;
}
