#include <iostream>
#include <algorithm>
#include <vector>
#include <stdio.h>

#define SUIT second
#define VAL first
typedef std::pair<int,char> Card;

char rval(int v) {
  switch(v) {
  case 14:
    return 'A';
  case 13:
    return 'K';
  case 12:
    return 'Q';
  case 11:
    return 'J';
  case 10:
    return 'T';
  default:
    return (char)(v+'0');
  }
}

std::ostream& operator<<(std::ostream& os, const Card &obj) {
  os << rval(obj.VAL) << obj.SUIT;
  return os;
}

int suitVal(char suit) {
  switch(suit) {
  case 'C':
    return 0;
  case 'D':
    return 1;
  case 'H':
    return 2;
  case 'S':
    return 3;
  default:
    return -1;
  }
}

bool operator<(const Card &a, const Card &b) {
  if(a.SUIT == b.SUIT)
    return a.VAL < b.VAL;
  return suitVal(a.SUIT) < suitVal(b.SUIT);
}

int val(char c) {
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

int main() {
  while(true) {
    std::vector<Card> cards[5];
    int scores[5];
    for(int i = 0; i < 5; ++i)
      scores[i] = 0;

    // Deal cards:
    std::string card;
    for(int i = 0; i < 50; ++i) {
      std::cin >> card;
      if(card[0] == '#')
	return 0;
      Card c(val(card[0]), card[1]);
      cards[(i+1)%5].push_back(c);
    }
    // Find trump card:
    std::cin >> card;
    Card trump;
    trump = Card(val(card[0]), card[1]);
    std::cin >> card;
    Card maybeBetter(val(card[0]), card[1]);
    if(trump.VAL < maybeBetter.VAL || (trump.VAL == maybeBetter.VAL && suitVal(trump.SUIT) < suitVal(maybeBetter.SUIT))) {
      trump = maybeBetter;
    }
    char trumpS = trump.SUIT;
    ///std::cerr << "Trump initially: " << trump << std::endl;    

    // Play game:
    int leader = 1;    
    for(int round = 0; round < 10; ++round) {
      ///std::cerr << "Round " << round << std::endl;
      for(int i = 0; i < 5; ++i) {
	///std::cerr << "Player " <<  (i+1) << " ";
	if(i == leader) {
	  ///std::cerr << "(leader) ";
	}
	for(unsigned int j = 0; j < cards[i].size(); ++j) {
	  ///std::cerr << cards[i][j] << " ";
	}
	///std::cerr << std::endl;
      }

      // pull cards:
      Card stack[5];
      // Play leader
      unsigned int leaderI = 0;
      for(unsigned int ci = 1; ci < cards[leader].size(); ++ci) {
	Card lci = cards[leader][ci];
	Card li = cards[leader][leaderI];
	if(lci.VAL > li.VAL) {
	  leaderI = ci;
	}
	else if(lci.VAL < li.VAL) {
	  // skip
	}	  
	else if(lci.SUIT == trump.SUIT) {
	  leaderI = ci;
	}
	else if(li.SUIT == trump.SUIT) {
	  // skip
	}
	else if(suitVal(lci.SUIT) > suitVal(li.SUIT)) {
	  leaderI = ci;
	}
      }
      stack[leader] = cards[leader][leaderI];
      char leaderS = stack[leader].SUIT;
      cards[leader].erase(cards[leader].begin()+leaderI);
      // play other players:
      for(int i = 0; i < 4; ++i) {
	int pos = (leader+1+i)%5;
	int posI = 0;
	for(unsigned int ci = 1; ci < cards[pos].size(); ++ci) {
	  Card c = cards[pos][ci]; // test
	  Card pc = cards[pos][posI]; // already choosen
	  if(c.SUIT == leaderS) {
	    if(pc.SUIT != leaderS || c.VAL > pc.VAL) {
	      posI = ci;
	    }
	  }
	  else if(c.SUIT == trumpS) {
	    if(pc.SUIT == leaderS)
	      continue;
	    if(pc.SUIT != trumpS || c.VAL > pc.VAL) {
	      posI = ci;  
	    }
	  }
	  else {
	    if(pc.SUIT == leaderS || pc.SUIT == trumpS)
	      continue;
	    if(c.VAL > pc.VAL || (c.VAL == pc.VAL && suitVal(c.SUIT) > suitVal(pc.SUIT)))
	      posI = ci;
	  }
	}
	stack[pos] = cards[pos][posI];
	cards[pos].erase(cards[pos].begin()+posI);
      }
      for(int i = 0; i < 5; ++i) {
	///std::cerr << ", " << (i+1);
	///std::cerr << ": " << stack[i];
	if(i == leader) {
	  ///std::cerr << "*";
	}
      }
      ///std::cerr << std::endl;

      // find winner of round: 
      leader = 0; // leader = winner!
      for(int i = 1; i < 5; ++i) {
	if(stack[i].SUIT == trumpS) {
	  if(stack[leader].SUIT != trumpS) {
	    leader = i;
	  }
	  else if(stack[leader].VAL < stack[i].VAL) {
	    leader = i;
	  }
	}
	else if(stack[i].SUIT == leaderS) {
	  if(stack[leader].SUIT == trumpS) {
	    continue;
	  }
	  else if(stack[leader].SUIT != leaderS) {
	    leader = i;
	  }
	  else if(stack[leader].VAL < stack[i].VAL) {
	    leader = i;
	  }
	}
      }
      ///std::cerr << "Player " << (leader+1) << " wins round: " << scores[leader];

      // give points:
      for(int i = 0; i < 5; ++i) {
	if(stack[i].SUIT == 'H') {
	  scores[leader] += stack[i].VAL;
	}
      }
      ///std::cerr << " -> " << scores[leader] << std::endl;
    }

    // OUTPUT POINTS:
    for(int i = 0; i < 5; ++i) {
      printf("%3i", scores[i]);
    }
    printf("\n");
  }
}
