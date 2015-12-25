import java.io.*;
import java.math.BigInteger;

public class P623 {
    private static BigInteger[] cache = new BigInteger[1001];
    private static int maxFac = 0;

    private static BigInteger fac(int n) {
	while(maxFac < n) {
	    cache[maxFac+1] = cache[maxFac].multiply(BigInteger.valueOf(maxFac+1));
	    ++maxFac;
	}
	return cache[n];
    }

    public static void main(String[] args) throws Exception {
	cache[0] = BigInteger.ONE;

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String l;
	while((l = br.readLine()) != null) {
	    int n = Integer.parseInt(l.trim());
	    System.out.println(n + "!");
	    System.out.println(fac(n));
	}
    }
}
