import java.io.*;
import java.math.BigInteger;

public class P10183 {
    private static BigInteger[] cache = new BigInteger[5001];
    private static int maxFib = 1;

    private static BigInteger fib(int n) {
	while(maxFib < n) {
	    cache[maxFib+1] = cache[maxFib].add(cache[maxFib-1]);
	    ++maxFib;
	}
	return cache[n];
    }

    public static void main(String[] args) throws Exception {
	cache[0] = BigInteger.ONE;
	cache[1] = BigInteger.ONE;

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String l;
	while((l = br.readLine()) != null) {
	    BigInteger a = new BigInteger(l.trim().split("\\s+")[0]);
	    BigInteger b = new BigInteger(l.trim().split("\\s+")[1]);
	    if(a.equals(BigInteger.ZERO) && b.equals(BigInteger.ZERO))
		return;

	    int idxA = 1;
	    while(fib(idxA).compareTo(a) != 1)
		++idxA;
	    --idxA;
	    int idxB = idxA;
	    while(fib(idxB).compareTo(b) != 1)
		++idxB;
	    --idxB;

	    int ret = idxB-idxA+1;
	    if(!fib(idxA).equals(a))
		--ret;
	    System.out.println(ret);
	    //System.err.println(fib(n).toString().length());
	}
    }
}
