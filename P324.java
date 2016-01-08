import java.io.*;
import java.math.BigInteger;

public class P324 {
    private static BigInteger[] cache = new BigInteger[367];
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
	while(true) {
	    int n = Integer.parseInt(br.readLine().trim());
	    if(n == 0)
		return;
	    System.out.println(n + "! --");
	    char[] digits = fac(n).toString().toCharArray();
	    int[] counts = new int[10];
	    for(char c : digits) {
		++counts[c-'0'];
	    }
	    for(int i = 0; i < 10; ++i) {
		System.out.printf("   (%d)%5d", i, counts[i]);
		if((i+1)%5 == 0)
		    System.out.println();
	    }
	}
    }
}
