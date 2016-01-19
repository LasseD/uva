import java.io.*;
import java.math.BigInteger;

public class P10929 {
    public static void main(String[] args) throws Exception {
	BigInteger b11 = BigInteger.valueOf(11);
	BigInteger b0 = BigInteger.ZERO;
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String line;
	while(null != (line = br.readLine())) {
	    BigInteger N = new BigInteger(line.trim());
	    if(N.equals(b0))
		return;
	    boolean divides11 = N.equals(N.divide(b11).multiply(b11));
	    System.out.println(line.trim() + " is" + (divides11 ? " ":" not ") + "a multiple of 11.");
	}
    }
}
