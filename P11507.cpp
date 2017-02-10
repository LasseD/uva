#define POSX 0
#define POSY 1
#define POSZ 2
#define NEGX 3
#define NEGY 4
#define NEGZ 5

int parse(const string &s) {
  if(s[0] == '+') {
    if(s[1] == 'y')
      return POSY;
    return POSZ;
  }
  else {
    if(s[1] == 'y')
      return NEGY;
    return NEGZ;
  }
}

int turnPosY(int from) {
  if(from == POSZ || from == NEGZ)
    return from;
  if(from == POSX)
    return POSY;
  if(from == NEGX)
    return NEGY;
  if(from == POSY)
    return NEGX;
  return POSX;
}

int turnPosZ(int from) {
  if(from == POSY || from == NEGY)
    return from;
  if(from == POSX)
    return POSZ;
  if(from == NEGX)
    return NEGZ;
  if(from == POSZ)
    return NEGX;
  return POSX;
}

int turn(int from, int dir) {
  switch(dir) {
  case POSY:
    return turnPosY(from);
  case NEGY:
    return turnPosY(turnPosY(turnPosY(from)));
  case POSZ:
    return turnPosZ(from);
  default:
    return turnPosZ(turnPosZ(turnPosZ(from)));    
  }
  // todo
}

int main() {
  while(true) {
    int L; cin >> L;
    if(L == 0)
      return 0;
    int dir = POSX;
    string s;
    FORI(L-1) {
      cin >> s;
      if(s != "No")
	dir = turn(dir, parse(s));
    }
    switch(dir) {
    case POSX:
      cout << "+x" << endl;
      break;
    case POSY:
      cout << "+y" << endl;
      break;
    case POSZ:
      cout << "+z" << endl;
      break;
    case NEGX:
      cout << "-x" << endl;
      break;
    case NEGY:
      cout << "-y" << endl;
      break;
    case NEGZ:
      cout << "-z" << endl;
      break;
    }
  }
}
