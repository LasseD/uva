int main() {
  int *x = new int[1000001];
  x[0] = 1;
  for(int i = 1; i <= 1000000; ++i) {
    x[i] = x[(int)(i-sqrt(i))] + x[(int)log(i)] + x[(int)(i*sin(i)*sin(i))];
    x[i] = x[i] % 1000000;
  }
  while(true) {
    GI(N); if(N == -1) return 0;
    cout << x[N] << endl;
  }
}
