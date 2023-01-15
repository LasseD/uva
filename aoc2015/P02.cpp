// Replace 'x' with ' ' in input.
int main() {
  LL answer1 = 0, sides[3], answer2 = 0;
  while(cin >> sides[0] >> sides[1] >> sides[2]) {
    sort(sides, &(sides[3]));
    answer1 += 3*sides[0]*sides[1] + 2*sides[0]*sides[2] + 2*sides[2]*sides[1];
    answer2 += 2*(sides[0]+sides[1]) + sides[0]*sides[1]*sides[2];
  }
  cout << "Answer 1: " << answer1 << endl;
  cout << "Answer 2: " << answer2 << endl;
}
