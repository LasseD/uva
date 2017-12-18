import java.math.BigInteger;
import java.util.Scanner;

public class P10814 {
    public static void main(String[] args) throws Exception {
	Scanner s = new Scanner(System.in);
	int cases = s.nextInt();
	for(int cas = 0; cas < cases; ++cas) {
	    BigInteger N = s.nextBigInteger();
	    s.next(); // "/"
	    BigInteger D = s.nextBigInteger();
	    BigInteger g = N.gcd(D);
	    N = N.divide(g);
	    D = D.divide(g);
	    System.out.println(N + " / " + D);
	}
    }
}
