#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

typedef pair<int,char> Card;
#define VALUE first
#define SUIT second

int valueToI(char c) {
  switch(c) {
  case 'A':
    return 14;
  case 'K':
    return 13;
  case 'Q':
    return 12;
  case 'J':
    return 11;
  case 'T':
    return 10;
  default:
    return c-'0';
  }
}

int two(Card *cards) {
  int highPair = -1;
  int lowPair = -1;
  for(int i = 1; i < 5; ++i) {
    if(cards[i].VALUE == cards[i-1].VALUE) {
      if(lowPair == -1)
	lowPair = cards[i].VALUE;
      else
	highPair = cards[i].VALUE;
    }
  }
  if(highPair == -1)
    return -1;
  int lastCard;
  if(cards[0].VALUE != lowPair)
    lastCard = cards[0].VALUE;
  else if(cards[4].VALUE != highPair)
    lastCard = cards[4].VALUE;
  else
    lastCard = cards[2].VALUE;
  
  cerr << "TWO PAIRS! " << endl;
  return 15*15*highPair + 15*lowPair + lastCard;
}

int house(Card *cards) {
  if(cards[0].VALUE != cards[1].VALUE)
    return -1;
  if(cards[3].VALUE != cards[4].VALUE)
    return -1;

  if(!(cards[1].VALUE == cards[2].VALUE || cards[2].VALUE == cards[3].VALUE))
    return -1;
  int ret = cards[2].VALUE;
  cerr << "HOUSE!: " << ret << endl;
  return ret;  
}
int straight(Card *cards) {
  for(int i = 1; i < 5; ++i) {
    if(cards[i].VALUE != cards[i-1].VALUE+1)
      return -1;
  }
  cerr << "STRAIGHT!: " << cards[4].VALUE << endl;
  return cards[4].VALUE;  
}
int flush(Card *cards) {
  for(int i = 1; i < 5; ++i) {
    if(cards[i].SUIT != cards[0].SUIT)
      return -1;
  }
  int ret = 0;
  for(int i = 4; i >= 0; --i) {
    ret = 15*ret + cards[i].VALUE;
  }
  cerr << "FLUSH!: " << ret << endl;
  return ret;
}
int straightFlush(Card *cards) {
  int s = straight(cards);
  if(s == -1)
    return -1;
  int f = flush(cards);
  if(f == -1)
    return -1;
  return s;
}
int four(Card *cards) {
  int p = -1;
  for(int i = 1; i >= 0; --i) {
    if(cards[i].VALUE == cards[i+1].VALUE && 
       cards[i].VALUE == cards[i+2].VALUE && 
       cards[i].VALUE == cards[i+3].VALUE) {
      p = cards[i].VALUE;
      break;
    }
  }
  if(p == -1)
    return -1;
  cerr << "FOUR!: " << p << endl;
  return p;
}
int three(Card *cards) {
  int p = -1;
  for(int i = 2; i >= 0; --i) {
    if(cards[i].VALUE == cards[i+1].VALUE && cards[i].VALUE == cards[i+2].VALUE) {
      p = cards[i].VALUE;
      break;
    }
  }
  if(p == -1)
    return -1;
  cerr << "THREE!: " << p << endl;
  return p;
}
int _pair(Card *cards) {
  int p = -1;
  for(int i = 3; i >= 0; --i) {
    if(cards[i].VALUE == cards[i+1].VALUE) {
      p = cards[i].VALUE;
      break;
    }
  }
  if(p == -1)
    return -1;
  int ret = p;
  for(int i = 4; i >= 0; --i) {
    if(p != cards[i].VALUE)
      ret = 15*ret + cards[i].VALUE;
  }
  cerr << "PAIR!: " << ret << endl;
  return ret;
}
int highCard(Card *cards) {
  int ret = 0;
  for(int i = 4; i >= 0; --i) {
    ret = 15*ret + cards[i].VALUE;
  }
  cerr << "High card: " << ret << endl;
  return ret;
}

int getValueOfHand(Card *cards) {
  for(int i = 0; i < 5; ++i) {
    cerr << " " << cards[i].VALUE << cards[i].SUIT;
  }
  cerr << endl;

  int ret;
  if(-1 != (ret = straightFlush(cards)))
    return 900000000 + ret;
  if(-1 != (ret = four(cards)))
    return 800000000 + ret;
  if(-1 != (ret = house(cards)))
    return 700000000 + ret;
  if(-1 != (ret = flush(cards)))
    return 600000000 + ret;
  if(-1 != (ret = straight(cards)))
    return 500000000 + ret;
  if(-1 != (ret = three(cards)))
    return 400000000 + ret;
  if(-1 != (ret = two(cards)))
    return 300000000 + ret;
  if(-1 != (ret = _pair(cards)))
    return 200000000 + ret;
  return highCard(cards);
}

int main() {
  Card cards[10];
  while(true) {
    // read cards:
    string card;
    for(int i = 0; i < 10; ++i) {
      if(!(cin >> card))
	return 0;
      cards[i] = Card(valueToI(card[0]), card[1]);
    }
    sort(cards, cards+5);
    sort(cards+5, cards+10);
    // Compare:
    int white = getValueOfHand(cards+5);
    int black = getValueOfHand(cards);
    if(white < black)
      cout << "Black wins." << endl;
    else if(white > black)
      cout << "White wins." << endl;
    else
      cout << "Tie." << endl;
  }
}
