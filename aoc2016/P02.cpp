int main() {
  string s;
  PI p(-2,0); // Assume middle is 0,0

  while(cin >> s) {
    FORUI(s.size()) {
      char c = s[i];
      switch(c) {
      case 'U':
	p.YY = max(-(2-abs(p.XX)), p.YY-1);
	break;
      case 'D':
	p.YY = min((2-abs(p.XX)), p.YY+1);
	break;
      case 'L':
	p.XX = max(-(2-abs(p.YY)), p.XX-1);
	break;
      case 'R':
	p.XX = min((2-abs(p.YY)), p.XX+1);
	break;
      default:
	die();
      }
    }
    // Output:
    switch(p.YY) {
    case -2:
      cout << "1";
      break;
    case -1:
      cout << p.XX+3;
      break;
    case 0:
      cout << p.XX+7;
      break;
    case 1:
      cout << (char)(p.XX + 1 + 'A');
      break;
    case 2:
      cout << "D";
      break;
    default:
      die();
    }
  }
  cout << endl;

  
  /* Part 1 below:
  PI p(1,1); // 5
  while(cin >> s) {
    FORUI(s.size()) {
      char c = s[i];
      switch(c) {
      case 'U':
	p.YY = max(0, p.YY-1);
	break;
      case 'D':
	p.YY = min(2, p.YY+1);
	break;
      case 'L':
	p.XX = max(0, p.XX-1);
	break;
      case 'R':
	p.XX = min(2, p.XX+1);
	break;
      default:
	die();
      }
    }
    // Output:
    cout << (1+3*p.YY) + p.XX;
  }
  cout << endl;
  //*/
}
