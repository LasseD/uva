int main() {
  FORCAS {
    if(cas != 0)
      cout << endl;
    int W, a, b; // = Columns
    cin >> W;
    int min = 200;
    int max = 0;
    FORY(W) {
      cin >> a >> b;
      int gap = a-b;
      min = MIN(min,gap);
      max = MAX(max,gap);
    }
    if(min == max)
      cout << "yes" << endl;
    else
      cout << "no" << endl;
  }
  return 0;
}
