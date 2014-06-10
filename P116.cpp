#include <stdio.h>
#include <iostream>
#include <stack>

int main() {
  // Read input:
  int m, n;
  int matrix[1000] = {0};
  int scores[1000] = {0};
  int back[1000] = {0};
  int lexScores[1000];

  while(std::cin >> m >> n) {
    for(int i = 0; i < m*n; ++i)
      lexScores[i] = -1;

    int v;
    for(int i = 0; i < m*n; ++i) {
      std::cin >> v;
      matrix[i] = v;
    }

    /*
    std::cerr << "MxN " << m << " x " << n << ":" << std::endl;
    for(int y = 0; y < m; ++y) {
      for(int x = 0; x < n; ++x) {
	std::cerr << matrix[y*n+x] << " ";
      }
      std::cerr << std::endl;
    }//*/

    // Build scores:
    // First row:
    for(int i = 0; i < m; ++i) {
      scores[i*n] = matrix[i*n];
      lexScores[i*n] = i;
    }
    // subsequent rows:
    for(int x = 1; x < n; ++x) {
      // build active:
      for(int y = 0; y < m; ++y) {
	int self = matrix[x+y*n];
	int prevY = (y+m-1)%m; // up
	int best = self + scores[prevY*n-1+x];
	int bestBack = prevY;
	for(int i = 0; i <= 1; ++i) {
	  prevY = (y+m+i)%m;
	  int candidate = self + scores[prevY*n-1+x];
	  if(candidate < best) {
	    best = candidate;
	    bestBack = prevY;
	  }
	  else if(candidate == best) {
	    // If lex score is better, choose it!
	    int bestLex = lexScores[bestBack*n-1+x];
	    int candidateLex = lexScores[prevY*n-1+x];
	    if(bestLex > candidateLex) {
	      best = candidate;
	      bestBack = prevY;
	    }
	  }
	}
	scores[y*n+x] = best;
	back[y*n+x] = bestBack;
      }
      // Update lexScores:
      int lexScore = 0;
      for(int i = 0; i < m; ++i) {
	// Find repvious row with score i:
	int prevYWithScore = 0;
	for(; prevYWithScore < m; ++prevYWithScore) {
	  if(lexScores[prevYWithScore*n+x-1] == i) {
	    break;
	  }
	}
	// check current row for users:
	int initPos;
	if(prevYWithScore == 0)
	  initPos = 1;
	else if(prevYWithScore == m-1)
	  initPos = 2;
	else
	  initPos = 0;
	for(int j = 0; j < 3; ++j) {
	  int tri = ((j + initPos + 3) % 3)-1;
	  int k = (tri+m+prevYWithScore)%m;
	  int index = k*n+x;
	  if(lexScores[index] == -1 && back[index] == prevYWithScore) {
	    //std::cerr << "setting for x=" << x << ", prev y=" <<  prevYWithScore << "-> y=" << k << " score=" << lexScore << "... j=" << j << ", k=" << k << ", tri=" << tri << std::endl;
	    lexScores[index] = lexScore++;
	  }
	}
	if(lexScore == m)
	  break;
      }
    }

    // debug info:
    /*
    std::cerr << "scores:" << std::endl;
    for(int y = 0; y < m; ++y) {
      for(int x = 0; x < n; ++x) {
	std::cerr << scores[y*n+x] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << "lexScores:" << std::endl;
    for(int y = 0; y < m; ++y) {
      for(int x = 0; x < n; ++x) {
	std::cerr << lexScores[y*n+x] << " ";
      }
      std::cerr << std::endl;
    }
    std::cerr << "back:" << std::endl;
    for(int y = 0; y < m; ++y) {
      for(int x = 0; x < n; ++x) {
	std::cerr << back[y*n+x] << " ";
      }
      std::cerr << std::endl;
      }//*/



    // Write output:
    // find best in last row:
    int row = 0;
    for(int i = 1; i < m; ++i) {
      if(scores[i*n+n-1] < scores[row*n+n-1])
	row = i;
      else if(scores[i*n+n-1] == scores[row*n+n-1]) {
	if(lexScores[i*n+n-1] < lexScores[row*n+n-1]) {
	  row = i;	  
	}
      }
    }
    int score = scores[row*n+n-1];
    std::stack<int> stack;
    for(int i = n-1; i >= 0; --i) {
      stack.push(row);
      row = back[row*n+i];
    }
    std::cout << (stack.top()+1);
    stack.pop();
    while(!stack.empty()) {
      std::cout << " " << (stack.top()+1);
      stack.pop();
    }
    std::cout << std::endl << score << std::endl;
  }
  
  return 0;
}
