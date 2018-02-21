int get(int N) { // Aka. Log_2(N) :D
  if(N == 1)
    return 1;
  int half = N/2;
  return 1 + get(half);
}

int main() {
  int N;
  while(cin >> N) {
    cout << get(N) << endl;
  }
  return 0;
}
