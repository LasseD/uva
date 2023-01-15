bool ok(int x) {
  int prev = 99;
  int digits[6];
  FORI(6) {
    int digit = x % 10;
    digits[i] = digit;
    if(prev < digit)
      return false;
    x /= 10;
    prev = digit;
  }
  // Find pair:
  FORI(5) {
    if(digits[i] == digits[i+1]) {
      bool lowOK = i == 0 || digits[i-1]!=digits[i];
      bool highOK = i+2 > 5 || digits[i+2]!=digits[i];
      if(lowOK && highOK)
	return true;
    }
  }
  return false;
}

int main() {
  GI(low); GI(high); int answer1 = 0;
  for(int i = low; i <= high; i++) {
    if(ok(i))
      answer1++;
  }
  cout << answer1 << endl;
}
