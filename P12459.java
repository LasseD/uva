import java.io.*;
import java.math.BigInteger;

public class P12459 {
    private static BigInteger[] cache = new BigInteger[82];
    private static int maxFib = 1;

    private static BigInteger fib(int n) {
	while(maxFib < n) {
	    cache[maxFib+1] = cache[maxFib].add(cache[maxFib-1]);
	    ++maxFib;
	}
	return cache[n];
    }

    public static void main(String[] args) throws Exception {
	cache[0] = BigInteger.ZERO;
	cache[1] = BigInteger.ONE;

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String l;
	while((l = br.readLine()) != null) {
	    int n = Integer.parseInt(l.trim());
	    if(n == 0)
		return;
	    System.out.println(fib(n+1));
	}
    }
}
