// Remove "x=", "y=", ":" from input!
// Add row of interest and max X/Y to input!
/*
?
?
x
x..S...B
x    
?  
?
 */

struct SB {
  PI S,B;
};

int dist(PI a, PI b) {
  return abs(a.XX-b.XX) + abs(a.YY-b.YY);
}
vector<SB> v;

bool canBe(PI Q) {
  bool canContainBeacon = true;
  FORIT(vector<SB>, v) {
    SB sb = *it;
    if(dist(Q, sb.B) == 0) {
      return true; // Already has beacon
    }
    if(dist(Q, sb.S) <= dist(sb.S, sb.B)) {
      canContainBeacon = false;
    }
  } // FORIT
  return canContainBeacon;
}

int main() {
  // Parse input:
  int a, b, c, d;
  string s;
  GI(roi); // Row of interest
  GI(MAXXY); // Max x/y
  int maxX = 0, maxY = 0, minX = 100000000, minY = 100000000;
  
  while(cin >> s >> s >> a >> b >> s >> s >> s >> s >> c >> d) {
    maxX = max(maxX, a);
    maxY = max(maxY, b);
    minX = min(minX, a);
    minY = min(minY, b);    
    maxX = max(maxX, c);
    maxY = max(maxY, d);
    minX = min(minX, c);
    minY = min(minY, d);
    SB sb; sb.S = PI(a,b); sb.B = PI(c,d);
    v.push_back(sb);
  }
  int W = maxX-minX;
  cout << "Map size: " << W << " X " << (maxY-minY) << endl;
  cout << "Min x = " << minX << endl;

  // Part 2: Sweep-line x->
  for(LL x = 0; x <= MAXXY; x++) {
    LL y = 0;
    while(y <= MAXXY) {
      // Find beacon that sees x,y, and set max y as 1 step out of range:
      int maxY = y;
      PI Q(x,y);
      FORIT(vector<SB>, v) {
	SB sb = *it;
	if(dist(Q, sb.S) <= dist(sb.S, sb.B)) {
	  maxY = max(maxY, sb.S.YY + dist(sb.B,sb.S) - abs((int)x-sb.S.XX) + 1);
	}
      }
      if(maxY == y) {
	if(canBe(Q)) {
	  // Not 3135800,2766584 : 3.135.800,2.766.584
	  
	}
	cout << "ANSWER 2: (" << canBe(Q) << ") " << x << "," << y << " => " << (x*4000000+y) << endl;
	die();
      }
      else {
	y = maxY;
      }
    } // while y
    
  } // FORX
  

  /* Part 1 below:
  // Investigate row
  cout << "Row of interest: " << roi << endl;

  int answer1 = 0;
  for(int x = minX-W; x < maxX+W; x++) {
    // Assume B on x,roi:
    PI Q(x,roi);
    bool canContainBeacon = true, hit = false;
    FORIT(vector<SB>, v) {
      SB sb = *it;
      if(dist(Q, sb.B) == 0) {
	hit = true;
	break;
      }
      if(dist(Q, sb.S) <= dist(sb.S, sb.B)) {
	canContainBeacon = false;
	//cout << "No beacon at " << x << ", " << roi << " Due to sensor " << sb.S.XX << ","<<sb.S.YY<<" seing "<<sb.B.XX<<","<<sb.B.YY<<endl;
      }
    } // FORIT
    if(!hit && !canContainBeacon) {
      if(answer1 == 0) {
	cout << "First beacon could not be at " << x << ", " << roi << endl;
      }
      answer1++;
    }
  } // for x
  cout << "Answer 1: " << answer1 << endl;
  //*/
} // int main
