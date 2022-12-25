// For ease of parsing, replace ",-" in input with spaces...
int main() {
  int sum1 = 0, sum2 = 0,a,b,c,d;
  while(cin >> a >> b >> c >> d) {
    if(a <= c && d <= b ||
       c <= a && b <= d) {
      sum1++;
      sum2++;
    }
    else if(a <= c && c <= b ||
	    a <= d && d <= b ||
	    c <= a && a <= d ||
	    c <= b && b <= d
	    ) {
      sum2++;
    }
  }
  cout << "Answer 1: " << sum1 << endl;
  cout << "Answer 2: " << sum2 << endl;
} // int main
