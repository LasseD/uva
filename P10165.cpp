/*
 Nim!
 Winning strategy iff. initial xor of pile sizes is 0. 
 */
int main() {
  while(true) {
    GI(N); if(N == 0) return 0;
    int sum = 0;
    FORI(N) {
      GI(M);
      sum ^= M;
    }
    if(sum == 0)
      cout << "No" << endl;
    else
      cout << "Yes" << endl;
  }
}
