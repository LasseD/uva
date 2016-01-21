import java.io.*;
import java.math.BigInteger;

public class P10220 {
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
	    String digits = fac(n).toString();
	    int sum = 0;
	    for(char c : digits.toCharArray())
		sum += c-'0';
	    System.out.println(sum);
	}
    }
}
