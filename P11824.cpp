int main() {
  LL a[50];
  FORCAS {
    int cnt = 0;
    while(true) {
      GI(n);
      if(n == 0)
	break;
      a[cnt++] = -n;
    }
    sort(a, a+cnt);
    LL ret = 0;
    bool expensive = false;
    FORI(cnt) {
      int n = -a[i];
      LL add = n;
      FORJ(i) {
	add *= n;
	if(2*add > 5000000) {
	  expensive = true;
	  break;
	}
      }
      ret += 2*add;
      if(expensive || ret > 5000000 || n > 5000000) {	
	expensive = true;
	break;
      }
    }
    if(expensive)
      cout << "Too expensive" << endl;
    else
      cout << ret << endl;
  }
  return 0;
}
