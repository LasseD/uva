typedef PC CARD; // Pair of chars. 

int suitIdx(char suit) {
  switch(suit) {
  case 'S':
    return 0;
  case 'H':
    return 1;
  case 'D':
    return 2;
  default:
    return 3;
  }
}

int rule1(char c) {
  switch(c) {
  case 'A':
    return 4;
  case 'K':
    return 3;
  case 'Q':
    return 2;
  case 'J':
    return 1;
  default:
    return 0;
  }
}

int main() {
  string s;
  vector<char> hand[4]; // suit -> cards
  bool stopped[4];

  while(true) {
    // Reset:
    FORI(4) {
      hand[i].clear();
      stopped[i] = false;
    }
    
    int pts = 0;
    int numStopped = 0;

    FORI(13) {
      if(!(cin >> s))
	return 0;
      hand[suitIdx(s[1])].push_back(s[0]);
      pts += rule1(s[0]);
    }

    // Rules 2-4:
    FORI(4) {
      FORIT(vector<char>, hand[i]) {
	char c = *it;
	if(c == 'K' && hand[i].size() == 1)
	  --pts; // Rule 2
	if(c == 'Q' && hand[i].size() <= 2)
	  --pts; // Rule 3
	if(c == 'J' && hand[i].size() <= 3)
	  --pts; // Rule 4
	// Find out if stopped:
	if(!stopped[i] && (c == 'A' || (c == 'K' && hand[i].size() >= 2) || (c == 'Q' && hand[i].size() >= 3))) {
	  stopped[i] = true;
	  ++numStopped;
	}
      }
    }

    if(pts >= 16 && numStopped == 4) {
      cout << "BID NO-TRUMP" << endl;
      continue;
    }

    // Rule 5 - 7:
    FORI(4) {
      if(hand[i].size() == 2)
	++pts; // Rule 5
      else if(hand[i].size() == 1)
	pts+=2; // Rule 6
      else if(hand[i].empty())
	pts+=2; // Rule 7
    }

    if(pts < 14) {
      cout << "PASS" << endl;
      continue;
    }

    char suits[4] = {'S', 'H', 'D', 'C'};
    int bestSuit = 0;
    for(int i = 1; i < 4; ++i) {
      if(hand[i].size() > hand[bestSuit].size())
	bestSuit = i;
    }
    cout << "BID " << suits[bestSuit] << endl;
  }
}
