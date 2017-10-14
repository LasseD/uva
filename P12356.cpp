/*
It turns out O(BlogS) is too slow. SO there is no time for using set.
 */
int main() {
  int LEFT[100001], RIGHT[100001];
  int S, B;
  while(true) {
    cin >> S >> B;
    if(S == 0 && B == 0)
      return 0;
    FORI(S) {
      LEFT[i] = i-1;
      RIGHT[i] = i+1;
    }
    RIGHT[S-1] = -1;

    FORI(B) {
      int L, R; cin >> L >> R; --L; --R;
      if(LEFT[L] == -1)
	cout << "*";
      else {
	cout << LEFT[L]+1;
	RIGHT[LEFT[L]] = RIGHT[R];
      }
      cout << " ";
      if(RIGHT[R] == -1)
	cout << "*";
      else {
	cout << RIGHT[R]+1;
	LEFT[RIGHT[R]] = LEFT[L];
      }
      cout << endl;
    }
    cout << "-" << endl;
  }
}
