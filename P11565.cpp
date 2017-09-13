/*
x+y+z = A
xyz = B
xx+yy+zz = C

a=A-x
b=B/x
c=C-xx
=>
yz=b => (a-z)z=b => zz-az+b=0 Solve for z:
 Discriminant "bb-4ac" = aa-4b
 Roots: "-b+-sqrt(d) / 2a" => z = a+-sqrt(d)/2

 Elimination: if x < 0 then equation 2 => y or z < 0. Since A>0 and y and z < 100, x >= -98 :S
 */
int main() {
  int A, B, C, solve[3], ret[3];
  FORCAS {
    ret[0] = ret[1] = ret[2] = 100;
    cin >> A >> B >> C;
    for(int x = -99; x <= 99; ++x) {
      if(x == 0 || B%x != 0)
	continue;
      int a = A-x;
      int b = B/x;
      // Find z:
      int d = a*a-4*b; // bb-4ac
      if(d < 0)
	continue; // no root
      for(int mult = -1; mult <= 1; mult +=2) {
	int z = (a+mult*(int)(0.00000000001+sqrt(d)))/2;
	int y = A-x-z;
	if(x+y+z == A && x*y*z == B && x*x+y*y+z*z == C && x != y && x != z && y != z) {
	  solve[0] = x;
	  solve[1] = y;
	  solve[2] = z;
	  sort(solve, solve+3);
	  if(solve[0] < ret[0] || (solve[0] == ret[0] && solve[1] < ret[1])) {
	    FORK(3)
	      ret[k] = solve[k];
	  }
	}
      } // for mult
    } // for x
    if(ret[0] == 100)
      cout << "No solution." << endl;
    else
      cout << ret[0] << " " << ret[1] << " " << ret[2] << endl;
  } // FORCAS
  return 0;
}
