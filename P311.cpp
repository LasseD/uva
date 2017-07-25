long fill2(long a, long b) {
  return (a + 4*b + 35)/36;
}

int main() {
  long S[6];
  while(true) {
    long sum = 0;
    FORI(6) {
      cin >> S[i];
      sum += S[i];
    }
    if(sum == 0)
      return 0;

    // 6x6 each get a box:
    sum = S[5]; 
    // 5x5 each get a box, but fill remainder with ones:
    long aroundFives = S[4]*11;
    sum += S[4];
    S[0] -= MIN(S[0], aroundFives);
    // 4x4 each get a box, but fill remainder with 2x2 and 1x1:
    long aroundFours = S[3]*5;
    sum += S[3];
    long fillTwos = MIN(S[1], aroundFours);
    long fillOnes;
    S[1] -= fillTwos;
    if(fillTwos < aroundFours) {
      fillOnes = 4*(aroundFours-fillTwos);
      S[0] -= MIN(S[0], fillOnes);
    }
    // 3x3: First remove all multiples of four, then sub-routine remainder:
    sum += S[2]/4;
    S[2] %= 4;
    switch(S[2]) {
    case 0:
      sum += fill2(S[0], S[1]);
      break;
    case 1:
      sum += 1;
      fillTwos = MIN(S[1], 5); // space for 5 around the 3x3
      S[1] -= fillTwos;
      fillOnes = 27 - 4*fillTwos;
      S[0] -= MIN(S[0], fillOnes);
      sum += fill2(S[0], S[1]);
      break;
    case 2: // Always put the two in same box:
      sum += 1;
      fillTwos = MIN(S[1], 3); // space for 3 around the two 3x3
      S[1] -= fillTwos;
      fillOnes = 18 - 4*fillTwos;
      S[0] -= MIN(S[0], fillOnes);
      sum += fill2(S[0], S[1]);
      break;
    default: // Case 3: -||-
      sum += 1;
      fillTwos = MIN(S[1], 1); // space for 1 around the three 3x3
      S[1] -= fillTwos;
      fillOnes = 9 - 4*fillTwos;
      S[0] -= MIN(S[0], fillOnes);
      sum += fill2(S[0], S[1]);
      break;
    }
    cout << sum << endl;
  }
}
