int main() {
  int posS[50000], posA[50000];
  FORCAS {
    GI(S); GI(A); GI(F);
    //LL sumS = 0, sumA = 0;
    FORI(F) {
      cin >> posS[i] >> posA[i];
    }
    sort(posS, posS+F);
    sort(posA, posA+F);

    cout << "(Street: " << posS[(F-1)/2] << ", Avenue: " << posA[(F-1)/2] << ")" << endl;
  }
  return 0;
}
