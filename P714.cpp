bool ok(const long max, const int m, const int k, long const * const pages) {
  //cerr << "Trying max=" << max;
  long stack = 0;
  int personI = 0;
  FORI(m) {
    stack += pages[i];
    if(stack > max) {
      stack = pages[i];
      ++personI;
      if(personI >= k) {
	//cerr << " Reached person " << k << "=> false" << endl;
	return false;
      }
    }
  }
  //cerr << " OK" << endl;
  return true;
}

int main() {
  long pages[500];
  FORCAS {
    int m, k; cin >> m >> k;
    long maxPages = -1, sumPages = 0;
    FORI(m) {
      cin >> pages[i];
      maxPages = MAX(pages[i], maxPages);
      sumPages += pages[i];
    }
    long lower = maxPages-1; // too little
    long upper = sumPages; // will have the result when done.
    while(lower < upper-1) {
      long mid = (upper+lower)/2;
      if(ok(mid, m, k, pages))
	upper = mid;
      else
	lower = mid;
    }
    //cerr << "m=" << m << ", k=" << k << ", Lower: " << lower << ", Upper: " << upper << endl;
    // Output:
    stack<int> booksPrScriber;
    long sum = 0;
    int cnt = 0;
    FORI(m) {
      sum += pages[m-1-i];
      ++cnt;
      int booksLeft = m-i;
      int peopleLeft = k-(int)booksPrScriber.size();
      if(sum > upper || booksLeft < peopleLeft) {
	booksPrScriber.push(cnt-1);
	cnt = 1;
	sum = pages[m-1-i];
      }
    }
    booksPrScriber.push(cnt);

    int bookIdx = 0;
    bool any = false;
    while(!booksPrScriber.empty()) {
      int booksForThis = booksPrScriber.top();
      booksPrScriber.pop();
      if(any)
	cout << " /";
      FORI(booksForThis) {
	if(any)
	  cout << " ";
	cout << pages[bookIdx++];
	any = true;
      }
    }
    cout << endl;
  }
  return 0;
}
