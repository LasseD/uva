import java.io.*;
import java.math.BigInteger;

public class P11879 {
    private static BigInteger b17 = BigInteger.valueOf(17);

    private static boolean divides(BigInteger nom, BigInteger denom) {
	return nom.equals(nom.divide(denom).multiply(denom));
    }

    private static boolean divides17(BigInteger nom) {
	return divides(nom, b17);
    }

    public static void main(String[] args) throws Exception {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	while(null != (line = br.readLine())) {
	    BigInteger N = new BigInteger(line.trim());
	    if(N.equals(BigInteger.ZERO))
	       return;
	    System.out.println(divides17(N) ? 1 : 0);
	}
    }
}
