int main() {
  PLL p(0,0), p2(0,0); string s; LL x, aim = 0;
  while(cin >> s >> x) {
    if(s[0] == 'f') {
      p.XX+=x;
      p2.XX+=x;
      p2.YY+=aim*x;
    }
    else if(s[0] == 'd') {
      p.YY+=x;
      aim+=x;
    }
    else {
      p.YY-=x;
      aim-=x;
    }
  }
  cout << p.XX*p.YY << endl;
  cout << p2.XX*p2.YY << endl;
}
