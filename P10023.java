import java.io.*;
import java.math.BigInteger;

public class P10023 {
    // http://stackoverflow.com/questions/4407839/how-can-i-find-the-square-root-of-a-java-biginteger
    public static BigInteger sqrt(BigInteger x) {
	BigInteger div = BigInteger.ZERO.setBit(x.bitLength()/2);
	BigInteger div2 = div;
	// Loop until we hit the same value twice in a row, or wind
	// up alternating.
	while(true) {
	    BigInteger y = div.add(x.divide(div)).shiftRight(1);
	    if (y.equals(div) || y.equals(div2))
		return y;
	    div2 = div;
	    div = y;
	}
    }

    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line = br.readLine();
	int cases = Integer.parseInt(line.trim());

	for(int i = 0; i < cases; ++i) {
	    br.readLine();
	    line = br.readLine();
	    if(i != 0)
		System.out.println();

	    BigInteger N = new BigInteger(line.trim());
	    System.out.println(sqrt(N));
	}
    }
}
