int main() {
  FORCAS {
    cout << "Case " << cas+1 << ": ";
    GI(N);
    map<string,int> S;
    FORI(N) {
      GS(s); GI(x); S[s] = x;
    }
    GI(D);
    GS(sub);    
    if(S.find(sub) == S.end() || S[sub] > D+5)
      cout << "Do your own homework!" << endl;
    else if(S[sub] <= D)
      cout << "Yesss" << endl;
    else
      cout << "Late" << endl;
  }
  return 0;
}
