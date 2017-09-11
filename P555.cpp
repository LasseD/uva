#define CLUBS 0
#define DIAMONDS 1
#define SPADES 2
#define HEARTS 3

#define NORTH 2
#define EAST 3
#define SOUTH 0
#define WEST 1

int getSuit(char c) {
  switch(c) {
  case 'C':
    return CLUBS;
  case 'D':
    return DIAMONDS;
  case 'S':
    return SPADES;
  default:
    return HEARTS;
  }
}
char toSuit(int i) {
  switch(i) {
  case CLUBS:
    return 'C';
  case DIAMONDS:
    return 'D';
  case SPADES:
    return 'S';
  default:
    return 'H';
  }
}
int getVal(char c) {
  if(isdigit(c))
    return c-'0';
  if(c == 'T')
    return 10;
  if(c == 'J')
    return 11;
  if(c == 'Q')
    return 12;
  if(c == 'K')
    return 13;
  return 14;
}
char toVal(int i) {
  if(i < 10)
    return i+'0';
  if(i == 10)
    return 'T';
  if(i == 11)
    return 'J';
  if(i == 12)
    return 'Q';
  if(i == 13)
    return 'K';
  return 'A';
}

int getDir(char c) {
  switch(c) {
  case 'N':
    return NORTH;
  case 'E':
    return EAST;
  case 'S':
    return SOUTH;
  default:
    return WEST;
  }
}

int main() {
  char dirs[4] = {'S', 'W', 'N', 'E'};
  string dealer, line1, line2, line;
  PI hands[4][13];
  while(true) {
    cin >> dealer;
    if(dealer[0] == '#')
      return 0;
    cin >> line1 >> line2;
    line = line1+line2;
    int dir = getDir(dealer[0]);
    FORI(52) {
      hands[(dir + 1 + i)%4][i/4] = PI(getSuit(line[2*i]), getVal(line[2*i+1]));
    }
    // Sort and output:
    FORI(4) {
      sort(hands[i], hands[i]+13);
    }
    FORI(4) {
      cout << dirs[i] << ":";
      FORJ(13)
	cout << " " << toSuit(hands[i][j].first) << toVal(hands[i][j].second);
      cout << endl;
    }
  }
}
