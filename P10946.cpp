void stepCC(int x, int y, int w, int h, char *field, stack<Point> &s, char color) {
  if(x < 0 || x >= w || y < 0 || y >= h)
    return;
  if(field[w*y+x] != color)
    return;
  s.push(Point(x, y));
}

// size connected component.
PIC getConnectedComponent(Point p, char *field, int w, int h) {
  char color = field[w*p.YY+p.XX];
  stack<Point> s;
  s.push(p);
  int size = 0;
  while(!s.empty()) {
    p = s.top();
    s.pop();
    if(field[w*p.YY + p.XX] == '.')
      continue; // Already handled.
    ++size;
    
    stepCC(p.XX-1, p.YY, w, h, field, s, color);
    stepCC(p.XX+1, p.YY, w, h, field, s, color);
    stepCC(p.XX, p.YY-1, w, h, field, s, color);
    stepCC(p.XX, p.YY+1, w, h, field, s, color);
    field[w*p.YY + p.XX] = '.';
  }
  //cerr << "Size of component " << color << ": " << size << " vs n=" << n << endl;
  return PIC(-size,color);
}

int main() {
  int w, h;
  string s;
  PIC ret[51*51];
  char field[51*51];

  for(int cas = 1; true; ++cas) {
    cin >> h >> w;
    if(w == 0 && h == 0)
      return 0;
    for(int y = 0; y < h; ++y) {
      cin >> s;
      FORX(w)
	field[y*w+x] = s[x];
    }

    int sizeRet = 0;
    FORX(w) {
      FORY(h) {
	if(field[w*y+x] == '.')
	  continue; // already handled.
	ret[sizeRet++] = getConnectedComponent(Point(x, y), field, w, h);
      }
    }
    sort(ret, ret+sizeRet);

    cout << "Problem " << cas << ":" << endl;
    FORI(sizeRet)
      cout << ret[i].second << " " << -ret[i].first << endl;
  }
}
