/*
0000  0
0001  1
0011  3
0010  2
0110  6
0111  7
0101  5
0100  4
1100 12
1101 13
1111 15
1110 14
1010 10
1011 11
1001  9
1000  8

 */
LL get(int n, LL pos) {
  if(n == 0)
    return 0;
  //cerr << "(" << n << "," << pos << ")";
  LL half = ((LL)1) << (n-1);
  if(pos >= half) { // 1-bit:
    return half + get(n-1, half-1-(pos-half));
  }
  else {
    return get(n-1, pos);
  }
}

int main() {
  FORCAS {
    int n;
    LL k;
    cin >> n >> k;

    //cerr << "n=" << n << ", k=" << k << " => ";

    cout << get(n, k) << endl;
  }
  return 0;
}
