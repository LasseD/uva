string trim(string s) {
  int size = (int)s.size();
  int start = 0;
  while(start < size && isspace(s[start]))
    ++start;
  if(start == size)
    return "";
  int end = size;
  while(end > start && isspace(s[end-1]))
    --end;
  if(end == start)
    return "";
  return s.substr(start, end-start);
}

int main() {
  string s;
  while(getline(cin, s)) {
    s = trim(s);
    int digits = 0, s1 = 0, s2 = 0;
    bool ok = true;

    FORUI(s.size()) {
      char c = s[i];
      if(c == '-')
	continue; // Ignore '-'
      if(isdigit(c)) {
	digits++;
	s1+=c-'0';
	s2+=s1;
      }
      else if(digits == 9 && c == 'X') {
	digits++;
	s1+=10;
	s2+=s1;
      }
      else {
	ok = false;
	break;
      }
    }
    if(ok && digits == 10 && s2%11 == 0) {
      cout << s << " is correct." << endl;
    }
    else {
      cout << s << " is incorrect." << endl;
    }
  }
  return 0;
}
