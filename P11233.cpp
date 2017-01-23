bool isWovel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';// || c == 'y';
}

int main() {
  int L, N;
  char from[111], to[111];
  map<string,string> irregular;
  scanf("%d %d\n", &L, &N);
  FORI(L) {
    scanf("%s %s\n", from, to);
    irregular[string(from)] = string(to);
  }
  FORI(N) {
    gets(to);
    string s(to);
    if(irregular.find(s) != irregular.end()) {
      cout << irregular[s] << endl;
    }    
    else if(s.size() >= 2 && s[s.size()-1] == 'y' && !isWovel(s[s.size()-2])) { // 2) end <consonant>y => ies:
      to[s.size()-1] = 'i';
      to[s.size()] = 'e';
      to[s.size()+1] = 's';
      to[s.size()+2] = '\0';
      cout << to << endl;
    }
    else if(s.size() >= 2 && s[s.size()-1] == 'h' && (s[s.size()-2]=='c' || s[s.size()-2]=='s')) { // 3) end sh/ch:
      to[s.size()] = 'e';
      to[s.size()+1] = 's';
      to[s.size()+2] = '\0';
      cout << to << endl;
    }
    else if(s.size() >= 1 && (s[s.size()-1] == 'o' || s[s.size()-1] == 's' || s[s.size()-1] == 'x')) { // 3) end o/s/x:
      to[s.size()] = 'e';
      to[s.size()+1] = 's';
      to[s.size()+2] = '\0';
      cout << to << endl;
    }
    else {
      to[s.size()] = 's';
      to[s.size()+1] = '\0';
      cout << to << endl;
    }
  }
  return 0;
} 
