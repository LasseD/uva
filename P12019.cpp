int main() {
  int lenOfMonth[12] = {31, 28, 31, 30,
			31, 30, 31, 31,
			30, 31, 30, 31};
  string days[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
  
  // jan 10 is monday, so jan 3 is also. jan 1 = saturday.
  FORCAS {
    GI(M); GI(D);
    --M; --D;
    int dayOfYear = D;
    for(int i = 0; i < M; ++i)
      dayOfYear += lenOfMonth[i];
    cout << days[dayOfYear%7] << endl;
  }
  return 0;
}
