import java.math.BigInteger;
import java.util.Scanner;

public class P10551 {
    public static void main(String[] args) throws Exception {
	Scanner s = new Scanner(System.in);
	while(true) {
	    int base = s.nextInt();
	    if(base == 0)
		return;
	    String p = s.next();
	    String m = s.next();
	    BigInteger P = new BigInteger(p, base);
	    BigInteger M = new BigInteger(m, base);
		    
	    System.out.println(P.remainder(M).toString(base));
	}
	
    }
}
