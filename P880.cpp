/*
Shells: 
0-0 size 1 vs 0
1-2      2    1
3-5      3    4
6-9      4    8

Discriminant b^2-4ac for solutions (-b+-root(b^2-4ac))/2a.

Shell s -> start index n
1 -> 0
2 -> 1
3 -> 3
4 -> 6
5 -> 10
n = s(s-1)/2
2n = s(s-1) = s^2-s
s^2-s-2n = 0
d = 1+8n
Solution: (1+-sqrt(1+8n))/2


index -> shell:
(int)sqrt(n-1)
 */
int main() {
  long N;
  while(cin >> N) {
    //cerr << "N=" << N << " -> ";
    --N;
    long shell = (1+(int)sqrt(1+8*N))/2;
    long under = (shell*(shell-1))/2;
    long remainder = N-under;
    //cerr << "Shell: " << shell << endl;

    cout << shell-remainder << "/" << remainder+1 << endl;
  }
  return 0;
}
