int main() {
  int cas = 1;
  while(true) {
    GI(N);
    if(N == 0)
      return 0;
    cout << "Case " << cas << ": " << (N+1)/2 << endl;
    ++cas;
  }
}
