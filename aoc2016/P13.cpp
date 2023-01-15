int fav;

bool isFree(PI &p) {
  LL x = p.first;
  LL y = p.second;
  if(x < 0 || y < 0)
    return false; // out of bounds
  LL test = x*x + 3*x + 2*x*y + y + y*y + fav;
  int ones = 0;
  while(test > 0) {
    if(test & 1) {
      ones++;
    }
    test >>= 1;
  }
  //cout << x << ", " << y << " Ones: " << ones << endl; 
  return ones % 2 == 0;
}

int main() {
  cin >> fav;
  set<PI> seen, s1, s2;
  PI p(1,1);
  seen.insert(p);
  s1.insert(p);
  
  for(int iteration = 0; iteration < 50; iteration++) {
    cout << "Iteration " << iteration << ": " << s1.size() << endl;
    FORIT(set<PI>, s1) {
      p = *it;
      int x = p.XX, y = p.YY;
      /*if(x == 31 && y == 39) { // Part 1
	cout << "Answer: " << iteration << endl;
	return 0;
      }*/
      
      for(int xx = x-1; xx <= x+1; xx++) {
	for(int yy = y-1; yy <= y+1; yy++) {
	  if(xx == x || yy == y) { // Ugly, but works. No diagonal moving.
	    PI p2(xx,yy);
	    if(isFree(p2) && seen.find(p2) == seen.end()) {
	      //cout << "Free: " << p2.XX << " " << p2.YY << endl;
	      s2.insert(p2);
	      seen.insert(p2);
	    } // if seen.find(p2)
	  } // if not diagonal
	} // for yy
      } // for xx
    } // FORIT
    
    swap(s1,s2);
    s2.clear();
  }
  cout << "Seen: " << seen.size() << endl;
}
