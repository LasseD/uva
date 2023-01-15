// Remove from input: "can fly ", "km/s for ", "seconds, but then must rest for ", and " seconds."
// Insert time in top of input
int main() {
  long t1[10], t2[10], speed[10], points[10], pos[10];  
  GI(T);
  FORI(10) {
    points[i] = pos[i] = 0;
  }
  string s;
  // Read reindeers:
  int N = 0;
  while(cin >> s >> speed[N] >> t1[N] >> t2[N]) {
    N++;
  }
  // Simulate:
  FORI(T) { // Each round
    long longest = 0;
    FORJ(N) { // Update positions:
      long cycleLength = t1[j]+t2[j];
      long positionInCycle = i % cycleLength;
      if(positionInCycle < t1[j]) {
	pos[j] += speed[j]; // Only move when not resting
      }
      longest = max(longest, pos[j]);
    }
    // Give points:
    FORJ(N) {
      if(pos[j] == longest) {
	points[j]++;
      }
    }
  }

  long best = 0;
  FORJ(N) {
    best = max(best, points[j]);
  }
  
  cout << "-------" << endl << "Answer: " << best << endl;
}
