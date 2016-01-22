import java.io.*;
import java.math.BigInteger;

public class P10070 {
    private static BigInteger b4 = BigInteger.valueOf(4);
    private static BigInteger b100 = BigInteger.valueOf(100);
    private static BigInteger b400 = BigInteger.valueOf(400);
    private static BigInteger b15 = BigInteger.valueOf(15);
    private static BigInteger b55 = BigInteger.valueOf(55);

    private static boolean divides(BigInteger nom, BigInteger denom) {
	return nom.equals(nom.divide(denom).multiply(denom));
    }

    private static boolean leap(BigInteger y) {
	if(!divides(y, b4))
	    return false;
	if(!divides(y, b100))
	    return true;
	return divides(y, b400);
    }
    
    private static boolean h(BigInteger y) {
	return divides(y, b15);
    }
    
    private static boolean b(BigInteger y) {
	return leap(y) && divides(y, b55);
    }

    public static void main(String[] args) throws Exception {

	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	boolean first = true;
	while(null != (line = br.readLine())) {
	    if(!first)
		System.out.println();
	    first = false;
	    BigInteger N = new BigInteger(line.trim());
	    boolean any = false;
	    if(leap(N)) {
		System.out.println("This is leap year.");
		any = true;
	    }
	    if(h(N)) {
		System.out.println("This is huluculu festival year.");
		any = true;
	    }
	    if(b(N)) {
		System.out.println("This is bulukulu festival year.");
		any = true;
	    }
	    if(!any)
		System.out.println("This is an ordinary year.");
	}
    }
}
