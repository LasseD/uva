int main() {
  int cnt[26];
  
  FORCAS {
    GI(R);GI(C);GI(M);GI(N);
    memset(cnt, 0, sizeof(cnt));
      
    FORI(R) {
      GS(S);
      FORUJ(S.size())
	++cnt[S[j]-'A'];
    }

    int maxCnt = 0;
    FORI(26)
      maxCnt = MAX(maxCnt, cnt[i]);

    int ret = 0;
    FORI(26) {
      if(cnt[i] == maxCnt)
	ret += M*cnt[i];
      else
	ret += N*cnt[i];
    }

    cout << "Case " << cas+1 << ": " << ret << endl;
  }
  return 0;
}
