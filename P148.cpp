#include <iostream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <algorithm>

#define BUFFER_SIZE 2000

struct Word {
  unsigned short letters[26];
  std::string word;
};

void zero(unsigned short* letters) {
  for(unsigned int i = 0; i < 26; ++i) {
    letters[i] = 0;
  }
}

void count(unsigned short* letters, const std::string &word) {
  zero(letters);
  for(unsigned int i = 0; i < word.size(); ++i) {
    ++letters[word[i]-'A'];
  }
}

void add(unsigned short* letters, const std::string &word) {
  for(unsigned int i = 0; i < word.size(); ++i) {
    if(word[i] >= 'A' && word[i] <= 'Z')
      ++letters[word[i]-'A'];
  }
}

bool fit(unsigned short* a, unsigned short const * const b) {
  for(int i = 0; i < 26; ++i) {
    if(a[i] < b[i])
      return false;
  }
  for(int i = 0; i < 26; ++i) {
    a[i]-=b[i];
  }
  return true;
}

void unfit(unsigned short* a, unsigned short const * const b) {
  for(int i = 0; i < 26; ++i) {
    a[i]+=b[i];
  }
}

bool ok(unsigned short* a, std::vector<std::string> &vector, const std::vector<std::string> &word) {
  for(int i = 0; i < 26; ++i) {
    if(a[i] != 0)
      return false;
  }
  if(vector.size() == word.size()) {
    std::string *sorted = new std::string[vector.size()];
    for(unsigned int i = 0; i < word.size(); ++i) {
      sorted[i] = word[i];
    }
    std::sort(sorted, &(sorted[word.size()]));
    bool same = true;    
    for(unsigned int i = 0; i < word.size(); ++i) {
      if(sorted[i] != vector[i]) {
	///std::cerr << "Not same because "<< *it << "!=" << vector[i-1] << std::endl;
	delete[] sorted;
	same = false;
	break;
      }
    }
    if(same) {
      delete[] sorted;
      return true;
    }
  }
  for(unsigned int i = 0; i < word.size(); ++i) {
    std::cout << word[i];
    std::cout << " ";
  }
  std::cout << "= ";
  for(unsigned int i = 0; i < vector.size(); ++i) {
    if(i != 0)
      std::cout << " ";
    std::cout << vector[i];
  }
  std::cout << std::endl;
  return true;
}

void find(unsigned short* letters, Word const * const dic, const int dicI, const int dicFrom, std::vector<std::string> &vector, const std::vector<std::string> &word) {
  if(dicI <= dicFrom)
    return;

  for(int i = dicFrom; i < dicI; ++i) {
    if(fit(letters, dic[i].letters)) {
      vector.push_back(dic[i].word);
      if(!ok(letters, vector, word))
	find(letters, dic, dicI, i+1, vector, word);
      vector.pop_back();
      unfit(letters, dic[i].letters);
    }
  }
}

int main() {
  Word dictionary[2000];  
  int dictionaryI = 0;
  std::string word;
  // build dictionary:
  char buffer[BUFFER_SIZE];
  while(true) {
    std::cin.getline(buffer, BUFFER_SIZE);
    if(buffer[0] == '#')
      break;
    int startI = -1;
    for(int i = 0; true; ++i) {
      if(buffer[i] >= 'A' && buffer[i] <= 'Z') {
	if(startI == -1)
	  startI = i;	
      }
      else {
	if(startI == -1)
	  continue;
	buffer[i] = '\0';
	word = std::string(&buffer[startI]);
	break;
      }
    }
    word = std::string(buffer);
    dictionary[dictionaryI].word = word;
    count(dictionary[dictionaryI].letters, word); 
    dictionaryI++;
  }
  // find anagrams:
  unsigned short letters[26];
  while(true) {
    std::cin.getline(buffer, BUFFER_SIZE);
    if(buffer[0] == '#')
      return 0;
    for(int i = 0; true; ++i) {
      if(buffer[i] == '\r' || buffer[i] == '\n') {
	buffer[i] = '\0';
	break;
      }
    }
    word = std::string(buffer);
    ///std::cerr << "Checking " << word << std::endl;
    std::vector<std::string> wordv;
    zero(letters);
    std::stringstream ss(word);
    std::string s;
    while(ss >> s) {
      add(letters, s);
      wordv.push_back(s);
    }
    std::vector<std::string> vector;
    find(letters, dictionary, dictionaryI, 0, vector, wordv);
  }
}
