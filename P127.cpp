#include <iostream>
#include <stack>

struct Card;
typedef std::stack<Card> CS;

struct Card {
  char suit;
  char value;

  bool matches(const Card &c) const {
    return suit == c.suit || value == c.value;
  }
};

std::ostream& operator<<(std::ostream& os, const Card& obj) {
  os << obj.value << obj.suit;
  return os;
}

void erase(CS *cards, int &cardsI, int i) {
  for(int j = i; j < cardsI-1; ++j) {
    std::swap(cards[j], cards[j+1]); 
  }
  --cardsI;
}

void addCard(CS *cards, int &cardsI, const Card &card) {
  //std::cerr << "Adding " << card << " to stack." << std::endl;
  if(cardsI == 0) {
    cards[cardsI++].push(card);
    //std::cerr << "Stack of one: " << card << std::endl;
    return;
  }
  int trickle = -1;
  if(cardsI >= 3 && cards[cardsI-3].top().matches(card)) {
    cards[cardsI-3].push(card);
    trickle = cardsI-3;
  }
  else if(cardsI >= 1 && cards[cardsI-1].top().matches(card)) {
    cards[cardsI-1].push(card);
    trickle = cardsI-1;
  }
  else {
    cards[cardsI++].push(card);
    //std::cerr << "Add no trickle: " << card << std::endl;
  }
  while(trickle >= 0) {
    Card c = cards[trickle].top();
    //std::cerr << "Testing trickle: " << c << " at " << trickle << std::endl;
    if(trickle >= 3 && cards[trickle-3].top().matches(c)) {
      cards[trickle].pop();
      if(cards[trickle].empty()) {
	erase(cards, cardsI, trickle);
      }
      cards[trickle-3].push(c);
      trickle -=3;
    }
    else if(trickle >= 1 && cards[trickle-1].top().matches(c)) {
      cards[trickle].pop();
      if(cards[trickle].empty()) {
	erase(cards, cardsI, trickle);
      }
      cards[trickle-1].push(c);
      trickle--;
    }
    else {
      ++trickle;
      if(trickle == cardsI)
	break;
    }
  }
  /*std::cerr << "Stack now:";
  for(int i = 0; i < cardsI; ++i) {
    std::cerr << " " << cards[i].top();
  }
  std::cerr << std::endl;//*/
}

int main() {
  char line[79];
  while(true) {
    CS cards[52];
    int cardsI = 0;

    std::cin.getline(line,79);
    if(line[0] == '#')
      return 0;

    for(int i = 0; i < 26; ++i) {
      Card card;
      card.value = line[i*3];
      card.suit = line[i*3+1];
      addCard(cards, cardsI, card);
    }
    std::cin.getline(line,79);
    for(int i = 0; i < 26; ++i) {
      Card card;
      card.value = line[i*3];
      card.suit = line[i*3+1];
      addCard(cards, cardsI, card);
    }
    // Handle stack:
    std::cout << cardsI << " pile" << (cardsI == 1 ? "" : "s") << " remaining:";
    for(int i = 0; i < cardsI; ++i) {
      std::cout << " " << cards[i].size();
    }
    std::cout << std::endl;
  }
}
