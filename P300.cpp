int main() {
  string haabMonths[20] = {"pop", "no", "zip", "zotz", "tzec", "xul", "yoxkin", "mol", "chen", "yax", "zac", "ceh", "mac", "kankin", "muan", "pax", "koyab", "cumhu", "uayet"};
  map<string,int> M;
  FORI(20)
    M[haabMonths[i]] = i;

  string TZOLKIN[20] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb",
			"ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};

  
  string haabDayS, haabMonthS;
  int haabYear;
  FORCAS {
    if(cas == 0)
      cout << cases << endl;
    cin >> haabDayS >> haabMonthS >> haabYear;
    int haabDay = 0;
    FORUJ(haabDayS.size()) {
      if(isdigit(haabDayS[j]))
	haabDay = 10*haabDay + haabDayS[j]-'0';
    }
    int dayOfWorld = 365*haabYear + 20*M[haabMonthS] + haabDay;
    int tzolkinYear = dayOfWorld/(13*20);
    int dayIndex = dayOfWorld%(13*20);
    cout << (dayIndex%13+1) << " " << TZOLKIN[dayIndex%20] << " " << tzolkinYear << endl;
  }
}
