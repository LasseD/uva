int main() {
  int size = 0, v[2010];
  while(cin >> v[size++])
    ;
  int answer = 0;
  for(int i = 3; i < size; i++) {
    if(v[i] > v[i-3]) {
      cout << "Larger at " << i << ": " << v[i] << endl;
      answer++;
    }
  }
  cout << answer << endl;
}
