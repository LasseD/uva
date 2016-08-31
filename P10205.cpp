#include <iostream>
#include <stdio.h>
#include <algorithm>

#define VAL first
#define SUIT second
typedef std::pair<int,int> Card;

std::ostream& operator<<(std::ostream& os, const Card &c) {
  if(c.VAL < 9)
    os << c.VAL+2;
  else if(c.VAL == 9)
    os << "Jack";
  else if(c.VAL == 10)
    os << "Queen";
  else if(c.VAL == 11)
    os << "King";
  else if(c.VAL == 12)
    os << "Ace";
  os << " of ";
  switch(c.SUIT) {
  case 0:
    os << "Clubs";
    break;
  case 1:
    os << "Diamonds";
    break;
  case 2:
    os << "Hearts";
    break;
  case 3:
    os << "Spades";
    break;
  }
  return os;
}

int main() {
  int cases, n, a[5200]; // n = number of shuffles. a = shuffles
  char line[52*4];
  Card cards[52], tmp[52];
  scanf("%d\n", &cases);
  for(int cas = 0; cas < cases; ++cas) {
    if(cas != 0)
      std::cout << std::endl;
    for(int suit = 0; suit < 4; ++suit) {
      for(int val = 0; val < 13; ++val)
	cards[13*suit+val] = Card(val, suit);
    }

    scanf("%d\n", &n);
    for(int i = 0; i < n; ++i)
      for(int j = 0; j < 52; ++j) {	
	scanf("%d", &a[52*i+j]);
	--a[52*i+j];
      }
    scanf("\n");
    //getchar();
    while(gets(line)) {
      int shuffle = atoi(line);
      if(shuffle == 0)
	break;
      //std::cerr << "Applying shuffle " << shuffle << std::endl;
      --shuffle;
      // copy to tmp:
      std::copy(cards, cards+52, tmp);
      for(int i = 0; i < 52; ++i)
	cards[i] = tmp[a[shuffle*52+i]];
    }
    // Output:
    for(int i = 0; i < 52; ++i)
      std::cout << cards[i] << std::endl;
  }
  return 0; 
}
