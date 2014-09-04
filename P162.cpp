#include <iostream>
#include <algorithm>
#include <deque>
#include <stdio.h>

#define VAL first
#define SUIT second
typedef std::pair<int,char> Card;

std::ostream& operator<<(std::ostream& os, const Card &obj) {
  os << obj.VAL << obj.SUIT;
  return os;
}

int ctoi(char c) {
  switch(c) {
  case 'A':
    return 4;
  case 'K':
    return 3;
  case 'Q':
    return 2;
  case 'J':
    return 1;
  case 'T':
    return 0;
  default:
    return 0;
  }
}

int main() {
  while(true) {
    std::deque<Card> d[3]; // player 1 (dealer), 2, stack

    int toPlayer = 1; // 0 is dealer
    for(int i = 0; i < 52; ++i) {
      std::string s;
      std::cin >> s;
      if(s[0] == '#')
	return 0;

      Card c(ctoi(s[1]), s[1]);
      d[toPlayer].push_back(c);
      toPlayer = 1-toPlayer;
    }

    // play:
    int mover = 1;
    bool done = false;
    while(!done) { // new round.
      /*
      std::cerr << "START OF ROUND. PLAYERS: " << std::endl;
      for(unsigned int i = 0; i < d[0].size(); ++i) {
	std::cerr << " " << d[0][i];
      }
      std::cerr << std::endl;
      for(unsigned int i = 0; i < d[1].size(); ++i) {
	std::cerr << " " << d[1][i];
      }
      std::cerr << std::endl;//*/

      // Can player place card?:
      if(d[mover].empty()) {
	mover = 1-mover;
	done = true;
	break;
      }

      if(d[2].empty() || d[2].back().VAL == 0) { // simply cover:
	Card c = d[mover].back();
	d[mover].pop_back();
	d[2].push_back(c);
	mover = 1-mover;
	continue;
      }

      // face card on stack. Need to cover!
      int toCover = d[2].back().VAL;
      bool won = true;
      for(int i = 0; i < toCover; ++i) {
	if(d[mover].empty()) {
	  mover = 1-mover;
	  done = true;
	  break;
	}
	Card c = d[mover].back();
	d[mover].pop_back();
	d[2].push_back(c);
	if(c.VAL != 0) {
	  mover = 1-mover;
	  won = false;
	  break;
	}
      }
      if(won && !done) { // done face stacking
	mover = 1-mover;
	while(!d[2].empty()) {
	  d[mover].push_front(d[2].front());
	  d[2].pop_front();
	}
      }
    }
    printf("%i %2i\n", mover+1, (int)d[mover].size());
  }
}
