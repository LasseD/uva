/*
  n = (a+dx)^3 = (a+dx)(a^2+2adx+dx^2) = a^3 + 3a^2dx + 3adx^2 + (( dx^3 ))
  n = a^3 + 3a^2dx + 3adx^2 => (n-a^3)/(3a) = adx + dx^2
  dx^2 + adx + (-n+a^3)/(3a) = 0
  dx = (-a +- sqrt(a^2-4c)) / (2a), c=(-n+a^3)/(3a)

  root(n) = a + dx

  THIS DOESN'T WORK. IT's TOO PRECISE!

  SO WHAT DOES THE PROBLEM DESCRIPTION MEAN WITH "GENERALIZE TO CUBIC ROOT!?"... I JUST HAVE TO GUESS...

  n = a^3 + 3a^2dx + (( 3adx^2 + dx^3 ))
  n = a^3 + 3a^2dx => dx = (n-a^3)/(3a^2)
 */
int main() {
  while(true) {
    GD(n);
    if(n == 0)
      return 0;
    long a = 1;
    while((a+1)*(a+1)*(a+1) <= n)
      ++a; // OK with slow walk because n is at least 1 and max 10^6

    /* Too precise:
    double c = (a*a*a-n)/(3*a);
    double dx = (-a + sqrt(a*a-4*c)) / (2*a); // Only consider the positive solution.
    */
    // Try less precise method:
    double dx = (n-a*a*a)/(3*a*a);
    // printf("%.6lf\n", a + dx); Use this debugging line to realize from the sample input that the word "upto" should have been "to".
    printf("%.4lf\n", a + dx);
  }
}
