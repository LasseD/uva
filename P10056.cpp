int main() {
  FORCAS {
    int N, pos;
    double p;
    cin >> N >> p >> pos;
    if(N == 1) {
      printf("%.4lf\n", p > 0 ? 1.0 : 0.0);
      continue;
    }

    double invP = 1-p;
    double noBefore = pow(invP, pos-1);
    double noRow = pow(invP, N);
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
