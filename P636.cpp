bool isSquare(ULL x, int B) {
  LL converted = 0, mult = 1;
  while(x > 0) {
    converted += mult*(x%10);
    mult *= B;
    x /= 10;
  }
  // Check if converted is square:
  LL high = converted; // Too much
  LL low = 0;
  while(low < high-1) {
    LL mid = (low+high)/2;
    if(mid*mid > converted)
      high = mid;
    else
      low = mid;
  }
  return low*low == converted;
}

int minBase(LL x) {
  int ret = 2;
  while(x > 0) {
    int digit = x%10;
    if(digit >= ret)
      ret = digit + 1;
    x /= 10;
  }
  return ret;
}

int main() {
  LL x;
  while(true) {
    cin >> x;
    if(x == 0)
      return 0;
    int B = minBase(x);
    for(; B < 100; ++B) {
      if(isSquare(x, B)) {
	cout << B << endl;
	break;
      }
    }
  }
}
