import java.io.*;
import java.math.BigInteger;

public class P10303 {
	public static void main(String[] args) throws Exception {
		BigInteger[] lookup = new BigInteger[1001];
		lookup[0] = lookup[1] = BigInteger.ONE;
		for(int i = 2; i <= 1000; ++i) {
			lookup[i] = BigInteger.ZERO;
		    for(int j = 0; j <= i-1; ++j) {
		    	BigInteger left = lookup[j];
		    	BigInteger right = lookup[i-1-j];
		    	lookup[i] = lookup[i].add(left.multiply(right));
		    }
		}

		BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
		String line;
		while(null != (line = rd.readLine())) {
			int N = Integer.parseInt(line.trim());
		    System.out.println(lookup[N].toString());
		}
	}
}
