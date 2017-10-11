int longestSubSequence(LL const * const s1, int lenS1, LL const * const s2, int lenS2) {
  if(lenS1 == 0 || lenS2 == 0)
    return 0;
  int *a = new int[2*(lenS1+1)]; // +1 for empty first character.
  int prevColumn = 0;
  for(int i = 0; i <= lenS1; ++i)
    a[i] = 0;
  for(int s2I = 0; s2I < lenS2; ++s2I) {
    int startI = (1-prevColumn)*(lenS1+1);
    int startPrevI = prevColumn*(lenS1+1);
    a[startI] = 0; // empty first character.
    for(int s1I = 0; s1I < lenS1; ++s1I) {
      if(s1[s1I] == s2[s2I]) {
	a[startI+s1I+1] = a[startPrevI+s1I] + 1;
      }
      else {
	int idxA = startI+s1I;
	int idxB = startPrevI+s1I+1;
	a[startI+s1I+1] = MAX(a[idxA], a[idxB]);
      }
      //std::cerr << a[startI+s1I+1] << " ";
    }
    prevColumn = 1-prevColumn;
    //std::cerr << std::endl;
  }

  int ret = a[prevColumn*(lenS1+1)+lenS1];
  delete[] a;
  return ret;
}

LL hashCode(string &s) {
  int ret = 0;
  FORUI(s.size()) {
    ret = 41*ret + s[i];
  }
  return ret;
}

void clean(string &s) {
  FORUI(s.size()) {
    if(!isalnum(s[i]))
      s[i] = ' ';
  }
}

int read(string s, LL *a) {
  stringstream ss;
  ss << s;
  int size = 0;
  while(ss >> s) {
    a[size++] = hashCode(s);
  }
  return size;
}

int main() {
  LL a[501], b[501];
  string s1, s2;
  for(int cas = 1; getline(cin, s1) && getline(cin, s2); ++cas) {
    if(s1.empty() || s2.empty()) {
      printf("%2d. Blank!\n", cas);
      continue; // Only blank if fully blank.
    }
    clean(s1);
    clean(s2);
    int sizeA = read(s1, a);
    int sizeB = read(s2, b);
    //cerr << "Size A: " << sizeA << ", size B: " << sizeB << endl;
    int ret = longestSubSequence(a, sizeA, b, sizeB);
    printf("%2d. Length of longest match: %d\n", cas, ret);
  }
  return 0;
}
