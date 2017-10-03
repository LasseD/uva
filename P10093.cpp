/*
Divisible by 9: https://www.khanacademy.org/math/pre-algebra/pre-algebra-factors-multiples/pre-algebra-divisibility-tests/v/the-why-of-the-9-divisibility-rule - Sum digits and ask for sum.

Take for base n:
R = r0r1...rx 
  = r0*n^x + r1*n^x-1 + rx*n^0
  = r0*(1+X*(n-1)) + ... rx*(1)
So R is div. by n-1 iff r0 + r1 + ... rx div by n-1.
 */
int decode(char c) {
  if(isdigit(c))
    return c-'0';
  if(c >= 'A' && c <= 'Z')
    return 10 + c-'A';
  else if(c >= 'a' && c <= 'z')
    return 36 + c-'a';
  return -1;
}

int main() {
  string line;
  while(getline(cin, line)) {    
    int minBase = 2;
    int sumDigits = 0;
    FORUI(line.size()) {
      char c = line[i];      
      int x = decode(c);
      if(x == -1)
	continue; // bad char.
      if(x >= minBase)
	minBase = x+1;
      sumDigits += x;
    }
    bool found = false;
    while(minBase <= 62) {
      if(sumDigits % (minBase-1) == 0) {
	found = true;
	cout << minBase << endl;
	break;
      }
      ++minBase;
    }
    if(!found)
      cout << "such number is impossible!" << endl;
  }
  return 0;
}
