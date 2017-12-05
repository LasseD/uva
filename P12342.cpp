int tax(int n) {
  // First 180000:
  if(n <= 180000)
    return 0;
  n -= 180000;
  double ret;
  // Next 300.000: 10% tax
  if(n <= 300000) {
    ret = n/10.0;
    if(ret < 2000)
      return 2000; // min amount.
    return (int)(ret + 1 - 1e-5);
  }  
  n -= 300000;
  ret = 30000;

  // Next 400.000: 15% tax
  if(n <= 400000) {
    ret += n*0.15;
    return (int)(ret + 1 - 1e-5);
  }  
  n -= 400000;
  ret += 400000*0.15;

  // Next 300.000: 20% tax
  if(n <= 300000) {
    ret += n*0.2;
    return (int)(ret + 1 - 1e-5);
  }  
  n -= 300000;
  ret += 300000*0.2;

  // Rest: 25% tax:
  ret += n*0.25;
  return (int)(ret + 1 - 1e-5);
}

int main() {
  FORCAS {
    GI(n);
    cout << "Case " << cas+1 << ": " << tax(n) << endl;
  }
  return 0;
}
