int main() {
  int a[100000];
  FORCAS {
    int n;
    cin >> n;

    FORI(n) {
      cin >> a[i];
    }

    int startK = a[0];
    int curK = startK-1;

    for(int i = 1; i < n; ++i) {
      int jump = a[i]-a[i-1];
      if(jump == curK) {
	--curK;
      }
      else if(jump > curK) { // Can't make it!
	if(jump < startK+1) {
	  ++startK;
	  curK = startK;
	}
	else {
	  startK = jump;
	  curK = startK-1;
	}
      }
    }
    cout << "Case " << cas+1 << ": " << startK << endl;
  }
}
