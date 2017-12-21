import java.math.*;
import java.util.Scanner;

public class P10081 {
    public static void main(String[] args) throws Exception {
	BigInteger HUNDRED = BigInteger.valueOf(100);
	String ret[][] = new String[8][101];

	BigInteger tight[][] = new BigInteger[10][101]; // 0..k, n

	for(int k = 2; k <= 9; ++k) {
	    BigInteger KPLUSONE = BigInteger.valueOf(k+1);
	    
	    for(int i = 0; i <= k; ++i)
		tight[i][1] = BigInteger.ONE; // One string of length 1 ends with i.
	    BigInteger ALL = KPLUSONE;
	    
	    for(int n = 2; n <= 100; ++n) {
		BigInteger SUM = BigInteger.ZERO;
		for(int i = 0; i <= k; ++i) {
		    tight[i][n] = tight[i][n-1];
		    if(i > 0)
			tight[i][n] = tight[i][n].add(tight[i-1][n-1]);
		    if(i < k)
			tight[i][n] = tight[i][n].add(tight[i+1][n-1]);
		    SUM = SUM.add(tight[i][n]);
		}

		// set ret:
		ALL = ALL.multiply(KPLUSONE);
		BigDecimal N = new BigDecimal(SUM.multiply(HUNDRED));
		BigDecimal D = new BigDecimal(ALL);
		ret[k-2][n] = N.divide(D, 5, BigDecimal.ROUND_HALF_UP).toPlainString();

	    }
	}
	
	Scanner s = new Scanner(System.in);
	while(s.hasNext()) {
	    int k = s.nextInt();
	    int n = s.nextInt();
	    if(k <= 1 || n <= 1)
		System.out.println("100.00000");
	    else
		System.out.println(ret[k-2][n]);
	}
	
    }
}
