int main() {
  set<PI> seen;
  PI p(0,0), q(0,0);
  seen.insert(p);
  GS(s);
  FORUI(s.size()) {
    char c = s[i];
    switch(c) {
    case '>':
      p.XX++;
      break;
    case '<':
      p.XX--;
      break;
    case '^':
      p.YY--;
      break;
    case 'v':
      p.YY++;
      break;
    default:
      die();
    }
    if(seen.find(p) == seen.end()) {
      seen.insert(p);
    }
    swap(p,q); // For part 2, include this line.
  }
  cout << "Answer: " << seen.size() << endl;
}
