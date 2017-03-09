// 131071 = 17 ones
int main() {
  char c;
  int X = 131071;
  while(true) {
    LL remainder = 0;
    while(true) {
      c = getchar();
      if(c == '0' || c == '1') {
	remainder = (remainder << 1) + (c == '1');
	if(remainder >= X)
	  remainder = remainder % X;
      }
      if(c == EOF)
	return 0;
      if(c == '#') 
	break;		
    }
    if(remainder == 0)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
}
