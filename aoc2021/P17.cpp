// Reduce input to just the numbers
int main() {
  GLL(miX); GLL(maX); GLL(miY); GLL(maY);
  cout << "Target area: x: " << miX << " -> " << maX << ", y: " << miY << " -> " << maY << endl;
  // Assume target area is x > 0

  // Part 1: Find max height:
  LL answer1 = -1, answer2 = 0;
  for(LL vx0 = maX; vx0 > 0; vx0--) {
    // Can we even reach target area?
    // 1+2+...vx0 =
    LL canReach = (vx0+1)*vx0/2;
    if(canReach < miX)
      break;
    cout << "TRY " << vx0;
    
    for(LL vy0 = miY; vy0 < 9999; vy0++) { // Arbitrary max that seems to work forme.
      LL x = 0, y = 0, vx = vx0, vy = vy0, maxY = y;
      bool wasEverBelowTarget = false, hit = false;

      // Simulate:
      do {
	// Update position and velocity:
	x += vx;
	y += vy;
	vx = max((LL)0, vx-1);
	vy--;
	// Update vars:
	maxY = max(maxY, y);
	if(x >= miX && x <= maX && y >= miY && y <= maY) {
	  hit = true;
	}	
	if(y < miY) {
	  wasEverBelowTarget = true;
	}
      } while(x <= maX && y >= miY);
      
      if(hit) {
	answer1 = max(answer1, maxY);
	answer2++;
	cout << " HIT " << answer2 << " on initial v: " << vx0 << ", " << vy0 << endl;
      }
      if(!wasEverBelowTarget) {
	break; // y too big
      }
      
    } // for vy0
  } // for vx0
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
