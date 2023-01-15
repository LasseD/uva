// Remove "," from input

int stats[10][5];
int N = 0, usage[10];
long best = 0;
int CAP = 100;
string names[10];

void go(int ingredient, int pos) {
  if(ingredient == N-1) {
    usage[N-1] = CAP-pos;
    long test = 1;
    cout << "Test ";
    FORJ(N) {
      cout << names[j] << usage[j] << " ";
    }
    FORI(4) { // Add for stat i (only 4 stats, not calories)
      long sum = 0;
      FORJ(N) { // Ingredient j
	sum += usage[j] * stats[j][i];
      }
      //cout << " " << sum << endl;
      sum = max(sum, 0L);
      test *= sum;
    }
    cout << "-> " << test << endl;

    // For part 2, compute calories:
    long calories = 0;
    FORJ(N) {
      calories += usage[j] * stats[j][4];
    }
    if(calories == 500) {
      best = max(best, test);
    }
    return;
  }
  for(int i = pos; i <= CAP; i++) {
    usage[ingredient] = i-pos;
    go(ingredient+1, i);
  }
}

int main() {
  // Read input:
  string s;
  cout << "STATS:" << endl;
  while(cin >> names[N]) {
    cout << names[N];
    FORI(5) {
      cin >> s >> stats[N][i];
      cout << " " << stats[N][i];
    }
    cout << endl;
    N++;
  }
  go(0, 0);
  cout << "Answer: " << best << endl;
}
