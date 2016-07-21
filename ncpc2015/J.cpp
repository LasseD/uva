#include <iostream>
#include <ctype.h>
#include <map>
#include <vector>
#include <string>

typedef std::vector<std::string> slist;
typedef std::vector<slist> sslist;

int readInts(int &a, int &b) {
  char w[100];
  std::cin.getline(w, 100);
  a = b = 0;
  bool aDone = false;
  for(int i = 0; isprint(w[i]); ++i) {
    char c = w[i];
    if(c >= '0' && c <= '9') {
      if(aDone) {
	b = 10*b+(c-'0');
      }
      else {
	a = 10*a+(c-'0');
      }
    }
    else
      aDone = true;
  }
}

int main() {
  int t, n;
  readInts(t, n);
  std::cerr << "Read ints t=" << t << ", n=" << n << std::endl;
  
  int maxWordsInQuestion = 0;
  slist answers;
  sslist questions;
  char w[300000];
  for(int i = 0; i < n; ++i) {
    std::cin.getline(w, 300000);
    int wStart = 0;
    bool isAnswer = false;
    for(int j = 0; j < 300000; ++j) {
      char c = w[j];
      else if(!isprint(w[j])) {
	w[i] = '\0';
	answers.push_back(std::string(&w[wStart]));
	break;
      }


      if(c == ' ') {
	if(isAnswer) {
	  continue;
	}
	else {
	  w[i] = '\0';
	  questions[i].push_back(std::string(&w[wStart]));
	  wStart = i+1;
	}
      }
      else if(c == '?') {
	if(isAnswer)
	  continue;
	isAnswer = true;
	w[i+1] = '\0';
	questions[i].push_back(std::string(&w[wStart]));
	wStart = i+2;	
	++i;
      }
    }
  }
  // Debugging:
  std::cerr << "Questions: " << std::endl;
  for(sslist::const_iterator it = questions.begin(); it != questions.end(); ++it) {
    const slist &ss = *it;
    for(slist::const_iterator it2 = ss.begin(); it2 != ss.end(); ++it2) {
      std::cerr << "'" << *it2 << "' ";
    }
    std::cerr << std::endl;
  }
  std::cerr << "Answers: " << std::endl;
  for(slist::const_iterator it = answers.begin(); it != answers.end(); ++it) {
    std::cerr << "'" << *it << "' " << std::endl;
  }
}
