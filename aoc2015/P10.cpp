int main() {
  GS(s);
  cout << "Init: " << s << endl;
  FORK(50) { // 40 for part 1
    stringstream ss;
    int i = 0;
    while(i < (int)s.size()) {
      int j = i;
      while(j+1 < (int)s.size() && s[j+1]==s[i]) {
	j++;
      }
      ss << "";
      ss << (char)('0'+((j-i)+1));
      ss << s[i];
      //cout << i << " Added " << ((j-i)+1) << " and " << s[i] << endl;
      i = j+1;
    }
    s = ss.str();
    cout << k << ": " << s << " size " << s.size() << endl;
  }
}
