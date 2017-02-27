int main() {
  FORCAS {
    int N, pos;
    double p;
    cin >> N >> p >> pos;
    double invP = 1.0/p;
    double noBefore = pow(invP, pos-1);
    double noRow = pow(p, N);
    double noRowN = noRow;
    double ret = noBefore * p;
    double ret2 = ret;
    do {
      ret = ret2;
      ret2 = ret + noRowN * noBefore * p;
      noRowN *= noRow;
    }
    while(ABS(ret-ret2) > 1e-7);
    printf("%.4lf\n", ret);
  }
  return 0;
}
