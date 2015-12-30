#include <iostream>

/*
S1[N] = 1  + 2  + 3  + .... + N = (1/2)N(N+1)
S2[N] = 12 + 22 + 32 + .... + N2 = (1/6)N(N+1)(2N+1)
S3[N] = 13 + 23 + 33 + .... + N3 = (1/4){N(N+1)}2

Compute Sn = 1^3+2^3+...+n^3

Assume there exists a polynomial:
1) Sn = a4n^4 + a3n^3 + a2n^2 + a1n + a0
2) S[n+1] = Sn + (n+1)^3

S0 =   0 => a0 = 0
S1 =   1 =>   1 =    a4 +   a3 +   a2 +  a1
S2 =   9 =>   9 =  16a4 +  8a3 +  4a2 + 2a1
S3 =  36 =>  36 =  81a4 + 27a3 +  9a2 + 3a1
S4 = 100 => 100 = 256a4 + 64a3 + 26a2 + 4a1

Q0: S2-2S1 =>                               7 =  14a4 +  6a3 +  2a2
Q1: S3-3S1 =>  33 =  78a4 + 24a3 +  6a2 => 11 =  26a4 +  8a3 +  2a2
Q2: 2S3-3S2 => 45 = 114a4 + 30a3 +  6a2 => 15 =  38a4 + 10a3 +  2a2
Q3: S4-4S1 =>  96 = 252a4 + 60a3 + 22a2 => 48 = 126a4 + 30a3 + 11a2

R0: Q1-Q0  =>  4 = 12a4 + 2a3 =>  2 =  6a4 +   a3
R1: Q2-Q1  =>                     4 = 12a4 +  2a3 
R2: Q2-Q0  =>                     8 = 24a4 +  4a3
R3: Q3-3Q2 =>                     3 = 12a4 +  0a3 + 5a2
R4: 9Q1-Q3 =>                    15 =        24a3 + 7a2

OK
T0: R1-R3 => 1 = 2a3 - 5a2 => 12 = 24a3 - 60a2
T1: R4-T0 => 3 = 67a2 =>      a2 = 3/67
T2: T0 => 1 = 2a3 - 5*3/67 => a3 = 41/67
T3: Q0 => 7 =  14a4 +  6a3 +  2a2

1): Sn = a4n^4 + a3n^3 + a2n^2 + a1n =>
    Sn = 1/16(11n^4 + 129n^3 + 9n^2 - 133n)

From web:
Sn = 1/4 * (n(n+1))^2 = 1/4 * n^2(n+1)^2 = 1/4 * n^2(n^2+2n+1) = 1/4 * (n^4+2n^3+n^2)

Check:
s0 = 0

 */
int main() {
  unsigned long long n;
  while(std::cin >> n) {
    unsigned long long top = n*(n+1);
    std::cout << top*top/4 << std::endl;
  }
  return 0;
}
