int main() {
  int N, M, agencies, A, B; // A: Price for one unit. B: Price for /2
  string line, agency;
  FORCAS {
    cout << "Case " << (cas+1) << endl;
    cin >> N >> M >> agencies; // N=Workload, M=target, agencies=L
    PULLS *ret = new PULLS[agencies];
    FORI(agencies) {
      cin >> line;
      FORUJ(line.size()) {
	if(line[j] == ',' || line[j] == ':')
	  line[j] = ' ';
      }
      stringstream ss;
      ss << line;
      ss >> agency >> A >> B;
      // Compute cost of agency:
      int rem = N;
      ULL cost = 0;
      // First reduce using B:
      while(rem/2 >= M && B < A*(rem-rem/2)) {
	rem/=2;
	cost+=B;
      }
      cost += A*(rem-M);
      ret[i] = PULLS(cost, agency);
    } // FORI
    sort(ret, ret+agencies);
    FORI(agencies) {
      cout << ret[i].second << " " << ret[i].first << endl;
    }
  } // FORCAS
  return 0;
}
