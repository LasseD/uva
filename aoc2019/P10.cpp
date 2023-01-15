typedef pair<PD,int> PDI;

int gcd(int a, int b) {
  int c;
  while(a != 0) {
     c = a; 
     a = b%a;  
     b = c;
  }
  return b;
}

double distSQ(PI &a, PI &b) {
  double dx = a.XX-b.XX;
  double dy = a.YY-b.YY;
  return dx*dx+dy*dy;
}

int main() {
  vector<PI> v;

  string s;
  int y = 0;
  while(getline(cin, s)) {
    FORUX(s.size()) {
      if(s[x] == '#') {
	v.push_back(PI(x,y));
      }
    }
    y++;
  }

  int best = 0;
  int bestI;
  FORUI(v.size()) {
    set<PI> angles;
    FORUJ(v.size()) {
      if(i ==j)
	continue;
      int dx = v[j].XX-v[i].XX;
      int dy = v[j].YY-v[i].YY;
      int g = gcd(abs(dx),abs(dy));
      dx/=g;
      dy/=g;
      angles.insert(PI(dx,dy));
    }
    if((int)angles.size() > best) {
      best = (int)angles.size();
      bestI = i;
    }
  }
  cout << "Answer 1: " << best << endl;

  PI q = v[bestI];
  cout << endl << q.XX << "," << q.YY << endl;
  PDI *v2 = new PDI[v.size()]; // angle, idx
  int sizeV2 = 0;
  FORUJ(v.size()) {
    if(j == bestI)
      continue;
    int dx = v[j].XX-q.XX;
    int dy = v[j].YY-q.YY;
    int g = gcd(abs(dx),abs(dy));
    dx/=g;
    dy/=g;
    double angle = atan2(dy,dx) + M_PI/2;
    if(angle < 0)
      angle += 2*M_PI;
    v2[sizeV2++] = PDI(PD(angle,distSQ(q,v[j])), j);
  }
  sort(v2, v2+sizeV2);
  FORI(sizeV2) {
    PDI w = v2[i];
    cout << "angle " << w.first.first << " dist " << w.first.second << " " << v[w.second].XX << "," << v[w.second].YY << endl;
  }
  int idx = 0;
  int cnt = 1;
  while(cnt <= 200) {
    double angle = v2[idx].first.first;
    int x = v[v2[idx].second].XX;
    int y = v[v2[idx].second].YY;
    cout << cnt++ << "= " << x << "," << y << " -> " << (100*x+y) << endl;

    // Erase idx from v2:
    for(int k = idx; k+1 < sizeV2; k++) {
      v2[k] = v2[k+1];
    }
    sizeV2--;

    // Update IDX:
    idx = idx%sizeV2;
    while(angle == v2[idx].first.first) {
      idx = (idx+1)%sizeV2;
    }
  }
}
