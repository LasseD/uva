import java.io.*;
import java.math.BigInteger;

public class P10106 {
    public static void main(String[] args) throws Exception {
	BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
	String l1, l2;
	while((l1 = br.readLine()) != null) {
	    l2 = br.readLine();
	    BigInteger b1 = new BigInteger(l1.trim());
	    BigInteger b2 = new BigInteger(l2.trim());
	    System.out.println(b1.multiply(b2));
	}
    }
}
