int main() {
  int *a = new int[690000];
  a[1] = 1;
  a[2] = 2;
  a[3] = 4;
  int i = 4;
  int j = 1;
  while(true) {
    while(a[j+1] <= i-1)
      ++j;
    a[i] = a[i-1]+j;
    //cerr << i << " -> " << a[i] << ", j=" << j << ", a[j]=" << a[j] << endl;
    if(a[i] > 2000100000)
      break;
    ++i;
  }

  int x;
  while(true) {
    cin >> x;
    if(x == 0)
      return 0;
    int high = i;
    int low = 1;
    while(high-low > 1) {
      int mid = (high+low)/2;
      if(a[mid] > x)
	high = mid;
      else
	low = mid;
    }
    
    cout << low << endl;
  }
}
