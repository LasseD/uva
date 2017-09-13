int decode(string &line, int &i) {
  int ret = 0;
  FORJ(5) {
    ret = (ret<<1) + line[i++]-'0';
  }
  return ret;
}
	   
int main() {
  string down, up, line;
  getline(cin, down);
  getline(cin, up);
  while(getline(cin, line)) {
    bool isDown = true;
    int i = 0;
    while(isdigit(line[i])) {
      int decoded = decode(line, i);
      if(decoded == 27)
	isDown = true;
      else if(decoded == 31)
	isDown = false;
      else if(isDown)
	cout << down[decoded];
      else
	cout << up[decoded];
    }
    cout << endl;
  }
  return 0;
}
