LL count(char *s, int len, LL mult) {
  LL answer = 0;

  FORI(len) {
    char c = s[i];
    if(c != '(') {
      //cout << "NORMAL " << c << endl;
      answer+=mult;
      continue;
    }
    // c == '(': Parse ints:
    int a = 0, b = 0;
    i++;
    while((c = s[i]) != 'x') {
      a = 10*a + (c-'0');
      i++;
    }
    // c == 'x'
    i++;
    while((c = s[i]) != ')') {
      b = 10*b + (c-'0');
      i++;
    }
    // c == ')'
    answer += mult * count(&s[i+1], a, b);
    i += a;    
  }
  return answer;
}

int main() {
  GS(s); cout << "INPUT " << s << endl;  
  cout << count(&s[0], (int)s.size(), 1) << endl; 
}
