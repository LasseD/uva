import java.io.*;
import java.math.BigInteger;

public class P10334 {
    private static BigInteger[] cache = new BigInteger[1001];
    private static int max = 1;

    private static BigInteger get(int n) {
	while(max < n) {
	    cache[max+1] = cache[max].add(cache[max-1]);
	    ++max;
	}
	return cache[n];
    }

    public static void main(String[] args) throws Exception {
	cache[0] = BigInteger.ONE;
	cache[1] = BigInteger.ONE.add(BigInteger.ONE);

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String l;
	while((l = br.readLine()) != null) {
	    int n = Integer.parseInt(l.trim());
	    System.out.println(get(n));
	}
    }
}
