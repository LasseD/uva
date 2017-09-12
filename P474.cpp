struct INV2N {
  long double d;
  int e;

  void half(INV2N o) {
    d = o.d*0.5;
    e = o.e;
    while(d < 1) {
      d*=10;
      ++e;
    }
  }

  void print() {
    printf("%.3Lfe-%d\n", d, e);
  }
};

int main() {
  INV2N *ret = new INV2N[1000000];
  ret[0].e = 1;
  ret[0].d = 5;
  
  for(int i = 1; i < 1000000; ++i) {
    ret[i].half(ret[i-1]);
  }

  /*for(int n = 1; n <= 10000; ++n) {
    printf("2^-%d = ", n);
    ret[n-1].print();
  }//*/
  int n;
  while(cin >> n) {
    printf("2^-%d = ", n);
    ret[n-1].print();
  }//*/
  return 0;
}
