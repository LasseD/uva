int gcd(int a, int b) {
  int c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

int main() {
  int a[1001];

  while(true) {
    int size = 0;
    while(cin >> a[size]) {
      if(a[size] == 0)
	break;
      ++size;
    }
    if(size < 2)
      return 0;
    sort(a, a+size);
    int g = a[1]-a[0]; // Maximal number that divides all differences.
    for(int i = 2; i < size; ++i) {
      g = gcd(g, a[i]-a[i-1]);
    }
    // Remember: if g=gcd(a,b) && g=gcd(b,c) then g=gcd(a,c)
    cout << g << endl;
  }
}
