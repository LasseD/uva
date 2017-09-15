import java.io.*;
import java.math.BigInteger;

/*
http://www.findstat.org/BinaryTrees => Number of binary trees = Catalan number.
http://www.geeksforgeeks.org/total-number-of-possible-binary-search-trees-with-n-keys/
Cat(n) = (2n)!/ ((n+1)!*n!)
 */
public class P10007 {
    public static void main(String[] args) throws Exception {
	// Exponents:
	BigInteger[] fac = new BigInteger[601];
	fac[0] = fac[1] = BigInteger.ONE;
	for(int i = 2; i < 601; ++i)
	    fac[i] = fac[i-1].multiply(BigInteger.valueOf(i));
	
	BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
	String line;
	while(null != (line = rd.readLine())) {
	    int N = Integer.parseInt(line.trim());
	    if(N == 0)
		return;
	    BigInteger catMultFacN = fac[2*N].divide(fac[N+1]);//.divide(fac[N]); // Catalan number if also divided with fac[N]
	    // Multiply with fac[N] to get permutations of numbered nodes in all trees.
	    System.out.println(catMultFacN);
	}
    }
}
