typedef pair<char,char> CARD;

int val(CARD c) {
  if(c.XX >= '2' && c.XX <= '9')
    return c.XX-'0';
  return 10;
}

int main() {
  FORCAS {
    vector<CARD> STACK, HAND;
    FORI(52-25) {
      GS(s);
      STACK.push_back(CARD(s[0],s[1]));
    }
    FORI(25) {
      GS(s);
      HAND.push_back(CARD(s[0],s[1]));
    }
    int Y = 0;
    FORI(3) {
      int X = val(*STACK.rbegin());
      //cerr << "VAL " << STACK.rbegin()->XX << STACK.rbegin()->YY << " = " << X << endl;
      Y += X;
      STACK.resize(STACK.size()-(1+10-X));
    }
    FORIT(vector<CARD>, HAND)
      STACK.push_back(*it);
    CARD &c = STACK[Y-1];
    cout << "Case " << cas+1 << ": " << c.XX << c.YY << endl;
  }
  return 0;
}
