#include <iostream>
#include <stdio.h>

#define LEN 10000

int readInt() {
  int ret = 0;
  int mult = 1;

  char w[20];
  gets(w);
  for(int i = 0; i < 20; ++i) {
    if(w[i] == '-') {
      mult = -1;
      continue;
    }
    if(!(w[i] >= '0' && w[i] <= '9'))
      break;
    ret = ret * 10 + (w[i]-'0');
  }
  return mult*ret;
}

int main() {
  bool toGuess[26], guessed[26];
  char c, word[LEN], guess[LEN];
  while(true) {
    int round = readInt();
    if(round == -1)
      return 0;
    std::cout << "Round " << round << std::endl;
    // Reset data:
    for(int i = 0; i < 26; ++i) {
      toGuess[i] = guessed[i] = false;
    }

    // Word to guess:
    gets(word);
    int left = 0;
    for(int i = 0; isprint(c = word[i]); ++i) {
      if(!toGuess[c-'a']) {
	toGuess[c-'a'] = true;
	++left;
      }
    }

    // Play game:
    int straws = 0;
    gets(guess);
    bool done = false;
    for(int i = 0; isprint(c = guess[i]); ++i) {
      if(guessed[c-'a'])
	continue;
      guessed[c-'a'] = true;
      if(toGuess[c-'a']) {
	--left;
	if(left == 0) {
	  done = true;
	  std::cout << "You win." << std::endl;
	  break;
	}
      }
      else {
	++straws;
	if(straws == 7) {
	  done = true;
	  std::cout << "You lose." << std::endl;
	  break;
	}
      }
    }
    if(!done)
      std::cout << "You chickened out." << std::endl;
  }
}
