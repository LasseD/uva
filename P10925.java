import java.math.BigInteger;
import java.util.Scanner;

public class P10925 {
    public static void main(String[] args) throws Exception {
	Scanner s = new Scanner(System.in);
	for(int cas = 1; true; ++cas) {
	    int N = s.nextInt();
	    int F = s.nextInt();
	    if(N == 0 && F == 0)
		return;
	    BigInteger sum = BigInteger.ZERO;
	    for(int i = 0; i < N; ++i) {
		sum = sum.add(s.nextBigInteger());
	    }
	    System.out.println("Bill #" + cas + " costs " + sum + ": each friend should pay " + sum.divide(BigInteger.valueOf(F)));
	    System.out.println();
	}
	
    }
}
