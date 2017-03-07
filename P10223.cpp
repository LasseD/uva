/*
http://www.findstat.org/BinaryTrees => Number of binary trees = Catalan number.
https://en.wikipedia.org/wiki/Catalan_number => Numbers.
 */
int main() {
  long long cat[23] = {
    1, 1, 2, 5, 14, 
    42, 132, 429, 1430, 4862, 
    16796, 58786, 208012, 742900, 2674440, 
    9694845, 35357670, 129644790, 477638700, 1767263190, 
    6564120420, 24466267020, 91482563640};
  long long N;
  while(cin >> N) {
    int ret = 1; // At least one node.
    while(cat[ret] < N)
      ++ret;
    cout << ret << endl;
  }
  return 0;
}
