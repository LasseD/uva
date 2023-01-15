int main() {
  GS(s);
  LL lv = 0, answer1 = 0, answer2 = 0;
  bool inGarbage = false;
  FORUI(s.size()) {
    char c = s[i];
    if(inGarbage) {
      switch(c) {
      case '>':
	inGarbage = false;
	break;
      case '!':
	i++; // skip next
	break;
      default:
	answer2++;
	break;
      }
    } // if inGarbage
    else {
      switch(c) {
      case '<':
	inGarbage = true;
	break;
      case '{':
	lv++;
	answer1 += lv;
	break;
      case '}':
	lv--;
	break;
      }
    } // not in garbage
  } // FORUI s
  cout << answer1 << endl;
  cout << answer2 << endl;
}
