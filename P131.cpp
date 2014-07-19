#include <iostream>
#include <algorithm>

#define SUIT second
#define VAL first
typedef std::pair<int,char> Card;

std::ostream& operator<<(std::ostream& os, const Card &obj) {
  os << obj.VAL << obj.SUIT;
  return os;
}

int numberOfSetBits(unsigned int i) {
  int res = 0;
  while(i != 0) {
    if((i & 1) == 1)
      ++res;
    i>>=1;
  }
  return res;
}

void testOnePair(int &highest, Card *hand) {
  if(highest >= 1)
    return;
  for(int i = 0; i < 4; ++i) {
    if(hand[i].VAL == hand[i+1].VAL) {
      highest = 1;
      return;
    }
  }
}

void testFlush(int &highest, Card *hand) {
  if(highest >= 5)
    return;
  if(hand[0].SUIT == hand[1].SUIT && 
     hand[0].SUIT == hand[2].SUIT && 
     hand[0].SUIT == hand[3].SUIT && 
     hand[0].SUIT == hand[4].SUIT) {
    highest = 5;
  }
}

void testStraightFlush(int &highest, Card *hand) {
  if(highest >= 8)
    return;
  if(hand[0].SUIT == hand[1].SUIT && 
     hand[0].SUIT == hand[2].SUIT && 
     hand[0].SUIT == hand[3].SUIT && 
     hand[0].SUIT == hand[4].SUIT) {
    if(0 == hand[0].VAL && 
       9 == hand[1].VAL && 
       10 == hand[2].VAL && 
       11 == hand[3].VAL && 
       12 == hand[4].VAL) {
      highest = 8;
    }
  }
}

void testThreeOfAKind(int &highest, Card *hand) {
  if(highest >= 3)
    return;
  for(int i = 0; i < 3; ++i) {
    if(hand[i].VAL == hand[i+1].VAL && hand[i+1].VAL == hand[i+2].VAL) {
      highest = 3;
      return;
    }
  }
}

void testFourOfAKind(int &highest, Card *hand) {
  if(highest >= 7)
    return;
  for(int i = 0; i < 2; ++i) {
    if(hand[i].VAL == hand[i+1].VAL && hand[i].VAL == hand[i+2].VAL && hand[i].VAL == hand[i+3].VAL) {
      highest = 7;
      return;
    }
  }
}

void testFullHouse(int &highest, Card *hand) {
  if(highest >= 6)
    return;
  if(hand[0].VAL == hand[1].VAL && hand[0].VAL == hand[2].VAL && hand[3].VAL == hand[4].VAL) {
      highest = 6;
      return;
  }
  if(hand[2].VAL == hand[3].VAL && hand[2].VAL == hand[4].VAL && hand[1].VAL == hand[0].VAL) {
      highest = 6;
      return;
  }
}

void testTwoPairs(int &highest, Card *hand) {
  if(highest >= 2)
    return;
  if(hand[0].VAL == hand[1].VAL && hand[2].VAL == hand[3].VAL) {
    highest = 2;
    return;
  }
  if(hand[0].VAL == hand[1].VAL && hand[3].VAL == hand[4].VAL) {
    highest = 2;
    return;
  }
  if(hand[1].VAL == hand[2].VAL && hand[3].VAL == hand[4].VAL) {
    highest = 2;
    return;
  }
}

void testStraight(int &highest, Card *hand) {
  if(highest >= 4)
    return;
  int i = 0;
  if(((hand[(i+0)%5].VAL+1)%13 == hand[(i+1)%5].VAL) &&
     ((hand[(i+1)%5].VAL+1)%13 == hand[(i+2)%5].VAL) &&
     ((hand[(i+2)%5].VAL+1)%13 == hand[(i+3)%5].VAL) &&
     ((hand[(i+3)%5].VAL+1)%13 == hand[(i+4)%5].VAL)) {
    highest = 4;
    return;
  }
}

int main() {
  std::string names[9];
  names[0] = "highest-card";
  names[1] = "one-pair";
  names[2] = "two-pairs";
  names[3] = "three-of-a-kind";
  names[4] = "straight";
  names[5] = "flush";
  names[6] = "full-house";
  names[7] = "four-of-a-kind";
  names[8] = "straight-flush";

  // mapping:
  int mapping[256];
  for(int i = 2; i <= 9; ++i) {
    mapping['0'+i] = i-1;
  }
  mapping['A'] = 0;
  mapping['T'] = 9;
  mapping['J'] = 10;
  mapping['Q'] = 11;
  mapping['K'] = 12;

  char line[32];
  Card cards[10];
  Card hand[5];
  while(std::cin.getline(line,32)) {    
    line[14] = '\0';
    line[29] = '\0';
    std::cout << "Hand: " << line << " Deck: " << &(line[15]) << " Best hand: ";

    // Read cards:
    for(int i = 0; i < 10; ++i) {
      char SUIT = line[3*i+1];
      char VAL = line[3*i];
      cards[i].SUIT = SUIT;
      cards[i].VAL = mapping[(int)VAL];
    }

    int best = 0;
    // test cards:
    for(unsigned int i = 0; i <= 0x1F; ++i) {
      unsigned int copyI = i;
      int stackI = 5;
      for(int handI = 0; handI < 5; ++handI) {
	if((copyI & 1) == 1) {
	  hand[handI] = cards[stackI++];	  
	}
	else {
	  hand[handI] = cards[handI];
	}
	copyI >>= 1;
      }
      std::sort(hand, &hand[5]);

      testStraightFlush(best, hand);      
      testFourOfAKind(best, hand);
      testFullHouse(best, hand);
      testFlush(best, hand);
      testStraight(best, hand);
      testThreeOfAKind(best, hand);
      testTwoPairs(best, hand);
      testOnePair(best, hand);
      /*
      std::cerr << "run tests for " << i << ": ";
      for(int j = 0; j < 5; ++j)
	std::cerr << hand[j] << " ";
      std::cerr << std::endl;
      std::cerr << names[best] << std::endl;//*/
    }
    
    std::cout << names[best] << std::endl;
  }
  return 0; 
}
